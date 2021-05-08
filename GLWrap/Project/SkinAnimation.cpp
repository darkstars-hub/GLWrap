#include "SkinAnimation.h"

#include "Helper.h"
#include "Application.h"


glm::mat4 my::SkinAnimation::ConputeAnimationTransform(const std::shared_ptr<my::ModelNode>& target) {
    if (_animations.size() == 0) {
        return glm::identity<glm::mat4>();
    } // if
    auto& animation = _animations.at(_current_animation_index);

    auto it = std::find_if(animation->anims.begin(), animation->anims.end(), [&](AnimData& data) {
        if (data.target.expired()) {
            return false;
        } // if
        return data.target.lock() == target;
    });
    if (it == animation->anims.end()) {
        return glm::identity<glm::mat4>();
    } // if
    auto& anim = *it;

    auto current_time = animation->time;
    auto prev_it = std::upper_bound(anim.key_frames.begin(), anim.key_frames.end(), current_time) - 1;
    auto next_it = std::upper_bound(anim.key_frames.begin(), anim.key_frames.end(), current_time);
    std::size_t prev_index = std::distance(anim.key_frames.begin(), prev_it);
    std::size_t next_index = std::distance(anim.key_frames.begin(), next_it);
    float interpolation = (current_time - *prev_it) / (*next_it - *prev_it);


    auto& prev_translation = anim.translations.at(prev_index);    auto& next_translation = anim.translations.at(next_index);
    auto& prev_rotate = anim.rotations.at(prev_index);    auto& next_rotate = anim.rotations.at(next_index);
    auto& prev_scale = anim.scales.at(prev_index);     auto& next_scale = anim.scales.at(next_index);

    auto translation = prev_translation + interpolation * (next_translation - prev_translation);
    auto rotate = glm::slerp(prev_rotate, next_rotate, interpolation);
    auto scale = prev_scale + interpolation * (next_scale - prev_scale);

    return
        glm::translate(glm::identity<glm::mat4>(), translation) *
        glm::toMat4(rotate) *
        glm::scale(glm::identity<glm::mat4>(), scale);
}

my::SkinAnimation::SkinAnimation() :
    _current_animation_index(0) {
}

my::SkinAnimation::~SkinAnimation() {
}

bool my::SkinAnimation::Initialize(my::GLTFData& gltf_data, std::vector<std::shared_ptr< my::ModelNode>>& nodes) {
    // animation
    for (auto& animation : gltf_data.animations) {
        auto pair = std::make_shared<AnimDataPair>();
        pair->name = animation.name;

        for (auto& channel : animation.channels) {
            auto anim = AnimData();

            auto& sampler = animation.samplers.at(channel.sampler_index);
            auto input = sampler.input_index;
            auto output = sampler.output_index;

            // input
            auto& time_accessor = gltf_data.accessors.at(input);
            anim.start_time = time_accessor.min.at(0);
            anim.end_time = time_accessor.max.at(0);

            std::vector<float>times;
            auto time_data = reinterpret_cast<float*>(gltf_data.BinaryData(input));

            anim.key_frames.reserve(time_accessor.count); anim.translations.reserve(time_accessor.count); anim.rotations.reserve(time_accessor.count); anim.scales.reserve(time_accessor.count);
            for (size_t i = 0; i < time_accessor.count; i++) {
                anim.key_frames.push_back(time_data[i]);
                anim.translations.push_back(glm::vec3());
                anim.rotations.push_back(glm::quat());
                anim.scales.push_back(glm::vec3(1.0f));
            } // for

            // output
            auto& output_accessor = gltf_data.accessors.at(output);

            if (channel.target.path == "translation") {
                auto translation_data = reinterpret_cast<float*>(gltf_data.BinaryData(output));
                for (size_t i = 0; i < output_accessor.count; i++) {
                    auto translation = glm::make_vec3(&translation_data[i * 3]);
                    anim.translations.at(i) = translation;
                } // for
            } // if
            if (channel.target.path == "rotation") {
                auto rotation_data = reinterpret_cast<float*>(gltf_data.BinaryData(output));
                for (size_t i = 0; i < output_accessor.count; i++) {
                    auto rotation = glm::make_quat(&rotation_data[i * 4]);
                    anim.rotations.at(i) = rotation;
                } // for
            } // if
            if (channel.target.path == "scale") {
                auto scale_data = reinterpret_cast<float*>(gltf_data.BinaryData(output));
                for (size_t i = 0; i < output_accessor.count; i++) {
                    auto scale = glm::make_vec3(&scale_data[i * 3]);
                    anim.scales.at(i) = scale;
                } // for
            } // if
            anim.target = nodes.at(channel.target.node_index);
            pair->anims.push_back(std::move(anim));
        } // for
        pair->start_time = pair->anims.at(0).start_time;
        pair->end_time = pair->anims.at(0).end_time;
        _animations.push_back(pair);
    } // for


    // skin

    for (auto& skin : gltf_data.skins) {
        //_animation_data.first;

        auto matrix_data = reinterpret_cast<float*>(gltf_data.BinaryData(skin.inverse_bind_matrices));
        auto& matrix_accessor = gltf_data.accessors.at(skin.inverse_bind_matrices);

        //_joint_data.second.inverse_binds.push_back(glm::identity<glm::mat4>());
        _joint_data.second.inverse_binds.push_back(nodes.at(0)->ConputeGlobalTransform());
        for (size_t i = 0; i < matrix_accessor.count; i++) {
            auto mat = glm::make_mat4(&matrix_data[i * 16]);
            _joint_data.second.inverse_binds.push_back(glm::transpose(mat));
            //_joint_data.second.inverse_binds.push_back(mat);
        } // for
        for (auto joint : skin.joints) {
            _joint_data.second.joints.push_back(joint);
        } // for
    } // for



    if (_joint_data.second.joints.size() != 0) {
        return true;
    } // if

    auto shader = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/mesh.shader");
    auto palette = JointMatrixPalette();
    shader->GenerateUniformBuffer("joint_matrices", sizeof(JointMatrixPalette), nullptr);

    return true;
}

bool my::SkinAnimation::Update(const std::shared_ptr<my::ModelNode>& target, const std::shared_ptr<my::Shader>& shader,
                               std::vector<std::shared_ptr<my::ModelNode>>& nodes) {
    shader->Enable();

    auto& animation = _animations.at(_current_animation_index);
    animation->time += 0.0167f;
//    animation->time = 0.0f;
    if (animation->end_time < animation->time) {
        animation->time = animation->start_time;
    } // if


    //globalTransformOfNodeThatTheMeshIsAttachedTo ^ -1 * メッシュがアタッチされているノードのグローバル変換 ^ -1
    //  globalTransformOfJointNode(j) * ジョイントノードのグローバル変換
    //  inverseBindMatrixForJoint(j); ジョイントの逆バインドマトリックス
    /*
    auto globalTransformOfNodeThatTheMeshIsAttachedTo = target->ConputeGlobalTransform();
    uint32_t index = 0;
    for (auto& matrix : _joint_matrix.matrices) {
        auto node_mat = target->ConputeGlobalTransform();
        auto anim_mat = this->ConputeAnimationTransform(target); //globalTransformOfJointNode;
        auto& inverse_bind = _joint_data.second.inverse_binds.at(index);
        matrix =  anim_mat * inverse_bind;
        index++;

        if (_joint_data.second.inverse_binds.size() == index) {
            break;
        } // if
    } // for
    */
    auto anim_mat0 = this->ConputeAnimationTransform(nodes.at(0));
    auto anim_mat1 = this->ConputeAnimationTransform(nodes.at(1));
    auto anim_mat2 = this->ConputeAnimationTransform(nodes.at(2));
    auto anim_mat = glm::identity<glm::mat4>(); //globalTransformOfJointNode;

    _joint_matrix.matrices.at(0) = anim_mat * _joint_data.second.inverse_binds.at(0);
    _joint_matrix.matrices.at(1) = anim_mat * _joint_data.second.inverse_binds.at(1);
    _joint_matrix.matrices.at(2) = anim_mat * _joint_data.second.inverse_binds.at(2);

    shader->BindUniformBuffer("joint_matrices", sizeof(_joint_matrix), &_joint_matrix);
    return true;
}