#include "KeyFrameAnimation.h"

#include "Helper.h"


my::KeyFrameAnimation::KeyFrameAnimation() :
    _animations(),
    _current_animation_index(0) {
}

my::KeyFrameAnimation::~KeyFrameAnimation() {
}

bool my::KeyFrameAnimation::Initialize(my::GLTFData& gltf_data, std::vector<std::shared_ptr<my::ModelNode>>& nodes) {
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
            if (channel.target.path == "weights") {
                auto& target = gltf_data.nodes.at(channel.target.node_index);
                auto& mesh = gltf_data.meshes.at(target.mesh_index);

                assert(mesh.primitives.size() == 1);


                _param.datas.reserve(mesh.primitives.at(0).targets.size());
                for (auto& target : mesh.primitives.at(0).targets) {
                    WeightData weight_data;
                    int position_index = target.position;
                    auto pos_data = reinterpret_cast<float*>(gltf_data.BinaryData(position_index));
                    auto& pos_accessor = gltf_data.accessors.at(position_index);


                    for (size_t i = 0; i < pos_accessor.count; i++) {
                        weight_data.positions.push_back(glm::make_vec3(&pos_data[i * 3]));
                    } // for
                    _param.datas.push_back(weight_data);
                } // for

                std::vector<std::vector<float>> work;
                work.resize(time_accessor.count);
                for (auto& v : work) {
                    v.resize(mesh.weights.size());
                } // for


                auto weights_data = reinterpret_cast<float*>(gltf_data.BinaryData(output));
                int i = 0;
                for (auto& v : work) {
                    for (auto& w : v) {
                        w = weights_data[i];
                        i++;
                    } // for
                } // for
                ut::VectorTranspose<float>(work, pair->weights);

                for (uint32_t index = 0; index < mesh.weights.size(); index++) {
                    _param.datas.at(index).weight = mesh.weights.at(index);
                } // for
            } // if

            anim.target = nodes.at(channel.target.node_index);
            pair->anims.push_back(std::move(anim));
        } // for
        pair->start_time = pair->anims.at(0).start_time;
        pair->end_time = pair->anims.at(0).end_time;
        _animations.push_back(pair);
    } // for

    return true;
}

bool my::KeyFrameAnimation::Update(void) {
    if (_animations.size() == 0) {
        return false;
    } // if
    auto& current_animation = _animations.at(_current_animation_index);

    current_animation->time += 0.0167f;
    if (current_animation->end_time <= current_animation->time) {
        current_animation->time = current_animation->start_time;
    } // if

    return true;
}

glm::mat4 my::KeyFrameAnimation::ConputeAnimationTransform(std::shared_ptr<my::ModelNode>& target) {
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

void my::KeyFrameAnimation::GenerateUniform(const std::shared_ptr<my::Shader>& shader) {
    if (_param.datas.size() == 0) {
        return;
    } // if
    shader->Enable();

    Weights w;
    shader->GenerateUniformBuffer("Weights", sizeof(Weights), &w);

    ::glGenBuffers(1, &_morph_handle);
    ::glBindBuffer(GL_SHADER_STORAGE_BUFFER, _morph_handle);
    ::glBufferData(GL_SHADER_STORAGE_BUFFER,
                 sizeof(glm::vec4) * 3,
                 nullptr, 
                 GL_STATIC_DRAW);
    ::glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _morph_handle);
}

void my::KeyFrameAnimation::BindUniform(const std::shared_ptr<my::Shader>& shader) {
    if (_animations.size() == 0) {
        return;
    } // if
    shader->Enable();
    auto& animation = _animations.at(_current_animation_index);
    auto& anim = animation->anims.at(0);
    auto current_time = animation->time;
    auto prev_it = std::upper_bound(anim.key_frames.begin(), anim.key_frames.end(), current_time) - 1;
    auto next_it = std::upper_bound(anim.key_frames.begin(), anim.key_frames.end(), current_time);
    std::size_t prev_index = std::distance(anim.key_frames.begin(), prev_it);
    std::size_t next_index = std::distance(anim.key_frames.begin(), next_it);
    float interpolation = (current_time - *prev_it) / (*next_it - *prev_it);

    auto& wv0 = animation->weights.at(0);
    auto& wv1 = animation->weights.at(1);

    auto& prev_w0 = wv0.at(prev_index);    auto& next_w0 = wv0.at(next_index);
    auto& prev_w1 = wv1.at(prev_index);    auto& next_w1 = wv1.at(next_index);
    auto w0 = prev_w0 + interpolation * (next_w0 - prev_w0);
    auto w1 = prev_w1 + interpolation * (next_w1 - prev_w1);

    _param.datas.at(0).weight = w0;
    _param.datas.at(1).weight = w1;

    auto w = Weights();
    int i = 0;
    for (auto& data : _param.datas) {
        w.weights.at(i) = data.weight;
        i++;
    } // for
    shader->SetIntUniform("morph_weight_size", 2);
    shader->BindUniformBuffer("Weights", sizeof(w), w.weights.data());

    std::array<glm::vec4,3>pos;
    i = 0;
    for (auto& v : _param.datas.at(0).positions) {
        pos[i] =  glm::vec4(v, 1.0f);
        i++;
    } // for

    

    ::glBindBuffer(GL_SHADER_STORAGE_BUFFER, _morph_handle);
    ::glBufferData(GL_SHADER_STORAGE_BUFFER,
                 sizeof(glm::vec4) * 3,
                 pos.data(), GL_STATIC_DRAW);
    ::glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _morph_handle);
}

void my::KeyFrameAnimation::ChangeAnimation(uint32_t index) {
    _current_animation_index = index;
}