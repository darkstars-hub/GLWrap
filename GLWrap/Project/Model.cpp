#include "Model.h"

#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Application.h"


bool my::Model::CreateNode(my::GLTFData& gltf_data) {
    auto remove_erase = []<class T>(std::vector<T>&container, std::function<bool()> condition) {
        auto it = std::remove_if(
            container.begin(),
            container.end(),
            [&](T elem) {
            return condition() == false;
        });
        container.erase(it, container.end());
    };

    _nodes.reserve(gltf_data.nodes.size());
    for (uint32_t i = 0; i < gltf_data.nodes.size(); i++) {
        _nodes.push_back(std::make_shared<my::ModelNode>());
    } // for

    int i = 0;
    for (auto& node : _nodes) {
        auto& node_data = gltf_data.nodes.at(i);
        node->Initialize(gltf_data, i, _nodes);

        for (auto child_index : gltf_data.nodes.at(i).child_indices) {
            auto& child = _nodes.at(child_index);
            node->AddChild(child);
            child->SetParent(node);
        } // for
        if (node_data.mesh_index != -1) {
            node->SetMesh(_meshes.at(node_data.mesh_index));
        } // if

        i++;
    } // for

    return true;
}

bool my::Model::CreateMesh(my::GLTFData& gltf_data) {
    _meshes.reserve(gltf_data.meshes.size());
    for (uint32_t i = 0; i < gltf_data.meshes.size(); i++) {
        auto ptr = std::make_shared<my::Mesh>();
        ptr->Initialize(gltf_data, i);
        if (int index = ptr->GetMaterialIndex(); index != -1) {
            ptr->SetMaterial(_materials.at(index));
        } // if
        _meshes.push_back(ptr);
    } // for

    return true;
}

bool my::Model::CreateMaterial(my::GLTFData& gltf_data) {
    _materials.reserve(gltf_data.materials.size());
    for (uint32_t i = 0; i < gltf_data.materials.size(); i++) {
        auto ptr = std::make_shared<my::Material>();
        ptr->Initialize(gltf_data, i);
        _materials.push_back(ptr);
    } // for
    return true;
}

my::Model::Model() :
    _name(),
    _nodes(),
    _meshes(),
    _key_frame_animation(),
    _skin_animation() {
}

my::Model::~Model() {
}

bool my::Model::Load(const char* path) {
    //! モデルデータ
    my::GLTFData gltf_data;

    if (!gltf_data.Load(path)) {
        return false;
    } // if
    _name = path;

    this->CreateMaterial(gltf_data);
    this->CreateMesh(gltf_data);
    this->CreateNode(gltf_data);
    auto s = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/mesh.shader");
    /*
    if (gltf_data.skins.size() != 0) {
        _skin_animation.Initialize(gltf_data, _nodes);
    } // if
    */
    if (gltf_data.meshes.at(0).weights.size() != 0) {
        _key_frame_animation.Initialize(gltf_data, _nodes);
        _key_frame_animation.GenerateUniform(s);
    } // if
    return true;
}

void my::Model::SetShader(const std::shared_ptr<my::Shader>& shader) {
    for (auto& node : _nodes) {
        node->SetShader(shader);
    } // for
}

bool my::Model::Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj) {
    auto transform =
        glm::translate(glm::identity<glm::mat4>(), position) *
        glm::toMat4(rotate) *
        glm::scale(glm::identity<glm::mat4>(), scale);
    this->Render(transform, view, proj);
    return true;
}


bool my::Model::Render(glm::mat4 transform, glm::mat4 view, glm::mat4 proj) {
    auto s = ::g_pResource->Get<std::shared_ptr<my::Shader>>("shader/mesh.shader");
    _key_frame_animation.Update();
    _key_frame_animation.BindUniform(s);
    //_skin_animation.Update(_nodes.at(0), s, _nodes);
    for (auto& node : _nodes) {
        node->Render(transform * node->ConputeGlobalTransform(), view, proj);
        //node->Render(transform, view, proj);
    } // for
    return true;
}