#include "ModelNode.h"


my::ModelNode::ModelNode() :
    _name(),
    _parent(),
    _children(),
    _local_transform(),
    _translation(),
    _rotation(),
    _scale(),
    _mesh() {
}

my::ModelNode::~ModelNode() {
}

void my::ModelNode::SetParent(const std::shared_ptr<my::ModelNode>& ptr) {
    this->_parent = ptr;
}

void my::ModelNode::SetMesh(const std::shared_ptr<my::Mesh>& ptr) {
    this->_mesh = ptr;
}

void my::ModelNode::SetShader(const std::shared_ptr<my::Shader>& shader) {
    if (auto mesh = _mesh.lock()) {
        mesh->SetShader(shader);
    } // if
}

void my::ModelNode::AddChild(const std::shared_ptr<my::ModelNode>& ptr) {
    this->_children.push_back(ptr);
}

bool my::ModelNode::Initialize(const my::GLTFData& data, int index, std::vector<std::shared_ptr<my::ModelNode>>& nodes) {
    auto& node = data.nodes.at(index);
    _name = node.name;
    _translation = node.translation;
    _rotation = node.rotation;
    _scale = node.scale;
    if (node.matrix.has_value()) {
        _local_transform = node.matrix.value();
    } // if
    else {
        _local_transform =
            glm::translate(glm::identity<glm::mat4>(), _translation) *
            glm::toMat4(_rotation) *
            glm::scale(glm::identity<glm::mat4>(), _scale);
    } // else

    return true;
}

glm::mat4 my::ModelNode::ConputeGlobalTransform(void) {
    if (auto parent = _parent.lock()) {
        return parent->ConputeGlobalTransform() * _local_transform;
    } // if
    return _local_transform;
}

bool my::ModelNode::Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj) {
    auto transform =
        glm::translate(glm::identity<glm::mat4>(), position) *
        glm::toMat4(rotate) *
        glm::scale(glm::identity<glm::mat4>(), scale);
    return this->Render(transform, view, proj);
}

bool my::ModelNode::Render(glm::mat4 transform, glm::mat4 view, glm::mat4 proj) {
    if (_mesh.expired()) {
        return false;
    } // if

    auto mesh = _mesh.lock();
//    mesh->Render(transform * this->ConputeGlobalTransform(), view, proj);
    mesh->Render(transform , view, proj);
    return true;
}