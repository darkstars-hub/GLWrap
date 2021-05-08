#include "Mesh.h"

#include "glm/gtx/matrix_decompose.hpp"


my::Mesh::Mesh() :
    _name(),
    _vertex_array(),
    _shader(),
    _material(),
    _material_index(-1) {
}

my::Mesh::~Mesh() {
}

void my::Mesh::SetShader(const std::shared_ptr<my::Shader>& ptr) {
    this->_shader = ptr;
    if (auto material = _material.lock()) {
        material->SetUniformLocation(ptr);
    } // if
}

void my::Mesh::SetMaterial(const std::shared_ptr<my::Material>& ptr) {
    this->_material = ptr;    
}

uint32_t my::Mesh::GetMaterialIndex(void) const {
    return this->_material_index;
}

bool my::Mesh::Initialize(my::GLTFData& gltf_data, int index) {
    auto& mesh = gltf_data.meshes.at(index);
    _name = mesh.name;

    // mesh
    std::vector<my::SkinVertex> vertices;
    std::vector<uint32_t> indices;
    assert(mesh.primitives.size() == 1);
    for (auto& primitive : mesh.primitives) {
        int position_index = primitive.attribute.position;
        int indices_index = primitive.indices;
        size_t indices_offset = vertices.size();

        if (position_index == -1 || indices_index == -1) { // ||//primitive.mode != GL_TRIANGLES
            break;
        } // if
        // vertices
        auto pos_data = reinterpret_cast<float*>(gltf_data.BinaryData(position_index));
        auto normal_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.normal));
        auto texcoord0_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.texcoord0));
        auto texcoord1_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.texcoord1));
        auto texcoord2_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.texcoord2));
        auto texcoord3_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.texcoord3));
        auto texcoord4_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.texcoord4));
        auto color_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.color));
        auto joint_data = reinterpret_cast<uint16_t*>(gltf_data.BinaryData(primitive.attribute.joint));
        auto weight_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.weight));
        auto tangent_data = reinterpret_cast<float*>(gltf_data.BinaryData(primitive.attribute.tangent));

        auto& pos_accessor = gltf_data.accessors.at(position_index);
        // í∏ì_èÓïÒäiî[
        for (size_t i = 0; i < pos_accessor.count; i++) {
            auto vertex = my::SkinVertex();
            vertex.position = glm::make_vec3(&pos_data[i * 3]);
            //std::swap(vertex.position.y, vertex.position.z);
            vertex.normal = normal_data ? glm::make_vec3(&normal_data[i * 3]) : glm::vec3(0.0f);
            vertex.texcoord0 = texcoord0_data ? glm::make_vec2(&texcoord0_data[i * 2]) : glm::vec2(0.0f);
            vertex.texcoord1 = texcoord1_data ? glm::make_vec2(&texcoord1_data[i * 2]) : glm::vec2(0.0f);
            vertex.texcoord2 = texcoord2_data ? glm::make_vec2(&texcoord2_data[i * 2]) : glm::vec2(0.0f);
            vertex.texcoord3 = texcoord3_data ? glm::make_vec2(&texcoord3_data[i * 2]) : glm::vec2(0.0f);
            vertex.texcoord4 = texcoord4_data ? glm::make_vec2(&texcoord4_data[i * 2]) : glm::vec2(0.0f);
            vertex.color = color_data ? glm::make_vec4(&color_data[i * 4]) : glm::vec4(0.0f);
            vertex.joints = joint_data ? glm::make_vec4(&joint_data[i * 8]) : glm::u16vec4(0);
            vertex.weights = weight_data ? glm::make_vec4(&weight_data[i * 4]) : glm::vec4(0.0f);
            vertex.tangent = tangent_data ? glm::make_vec4(&tangent_data[i * 4]) : glm::vec4(0.0f);
            vertices.push_back(vertex);
        } // for
        // indices
        auto& indices_accessor = gltf_data.accessors.at(indices_index);
        if (indices_accessor.component_type == GL_UNSIGNED_INT) {
            auto indices_data = reinterpret_cast<uint32_t*>(gltf_data.BinaryData(indices_index));
            for (size_t i = 0; i < indices_accessor.count; i++) {
                auto index = indices_data[i];
                indices.push_back(index + indices_offset);
            } // for
        } // if
        else if (indices_accessor.component_type == GL_UNSIGNED_SHORT) {
            auto indices_data = reinterpret_cast<uint16_t*>(gltf_data.BinaryData(indices_index));
            for (size_t i = 0; i < indices_accessor.count; i++) {
                auto index = static_cast<uint32_t>(indices_data[i]);
                indices.push_back(index + indices_offset);
            } // for
        } // else if
        else if (indices_accessor.component_type == GL_UNSIGNED_BYTE) {
            auto indices_data = reinterpret_cast<uint8_t*>(gltf_data.BinaryData(indices_index));
            for (size_t i = 0; i < indices_accessor.count; i++) {
                auto index = static_cast<uint32_t>(indices_data[i]);
                indices.push_back(index + indices_offset);
            } // for
        } // else if

        if (primitive.material != -1) {
            _material_index = primitive.material;
        } // if

        _vertex_array = my::VertexArray<my::SkinVertex>(vertices, indices);
        _vertex_array.Generate();
        _vertex_array.ToTriangles();
    } // for
    return true;
}

bool my::Mesh::Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj) {
    auto translation = glm::translate(glm::identity<glm::mat4>(), position);
    auto rotation = glm::toMat4(rotate);
    auto scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(scale));
    auto transform = translation * rotation * scaling;

    return this->Render(transform, view, proj);
}

bool my::Mesh::Render(glm::mat4 transform, glm::mat4 view, glm::mat4 proj) {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    // ÉZÉbÉg
    shader->Enable();
    shader->SetMatrixUniform("transform", transform);
    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);

    if (auto material = _material.lock()) {
        material->Enable(shader);
    } // if
    
    _vertex_array.Bind();
    _vertex_array.Render();
    return true;
}