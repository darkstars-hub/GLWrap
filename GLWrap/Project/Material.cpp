#include "Material.h"


bool my::Material::LoadTexture(int texture_index, my::GLTFData& gltf_data, TextureSlot& out) {
    auto& directory_path = gltf_data.directory_path;
    auto& texture = gltf_data.textures.at(texture_index);
    auto& image = gltf_data.images.at(texture.source_image_index);
    my::Texture::ImageData image_data;
    if (!image_data.Load(std::string(directory_path + image.uri).c_str())) {
        return false;
    } // if

    _texture.Bind(out.location);
    _texture.WriteImage(image_data);
    _texture.GenerateMipMap();

    image_data.Release();
    out.enable = true;
    return true;
}

my::Material::Material() :
    _name(),
    _texture(),
    _slots() {
    _slots = {
        TextureSlot("base_color_texture", 0,"enable_base_color", "base_color_texcoord_index"),
        TextureSlot("metallic_roughness_texture", 1,"enable_metallic_roughness_color","metallic_roughness_texcoord_index"),
        TextureSlot("normal_texture", 2,"enable_normal_color","normal_texcoord_index"), // 1テクセル単位で反射する光の強さ
        TextureSlot("occlusion_texture", 3,"enable_occlusion_color","occlusion_texcoord_index"),
        TextureSlot("emissive_texture", 4,"enable_emissive_color","emissive_texcoord_index"),
    };
}

my::Material::~Material() {
    _texture.Release();
}

void my::Material::SetUniformLocation(const std::shared_ptr<my::Shader>& shader) {
    shader->Enable();

    for (auto& slot : _slots) {
        if (slot.enable) {
            _texture.Bind(slot.location);
            shader->SetIntUniform(slot.name.c_str(), slot.location);
        } // if
    } // for
    
    shader->Disable();
}

bool my::Material::Initialize(my::GLTFData& gltf_data, int index) {
    auto& directory_path = gltf_data.directory_path;
    auto& material = gltf_data.materials.at(index);

    _name = material.name;
    _texture.GenerateTexture(_slots.size());

    auto set_texcoord = [](auto& slot, auto& data) {
        if (data.texcoord_index != 0) { slot.texcoord_index = data.texcoord_index; } // if
    };
    if (auto& tex_data = material.pbr_metallic_roughness.base_color_texture; tex_data.texture_index != -1) {
        auto& slot = _slots.at(0);
        if (!this->LoadTexture(tex_data.texture_index, gltf_data, slot)) {
            return false;
        } // if
        set_texcoord(slot, tex_data);
    } // if
    if (auto& tex_data = material.pbr_metallic_roughness.metallic_roughness_texture; tex_data.texture_index != -1) {
        auto& slot = _slots.at(1);
        if (!this->LoadTexture(tex_data.texture_index, gltf_data, slot)) {
            return false;
        } // if
        set_texcoord(slot, tex_data);
    } // if
    if (auto& tex_data = material.normal_texture; tex_data.texture_index != -1) {
        auto& slot = _slots.at(2);
        if (!this->LoadTexture(tex_data.texture_index, gltf_data, slot)) {
            return false;
        } // if
        set_texcoord(slot, tex_data);
    } // if
    if (auto& tex_data = material.occlusion_texture; tex_data.texture_index != -1) {
        auto& slot = _slots.at(3);
        if (!this->LoadTexture(tex_data.texture_index, gltf_data, slot)) {
            return false;
        } // if
        set_texcoord(slot, tex_data);
    } // if
    if (auto& tex_data = material.emissive_texture; tex_data.texture_index != -1) {
        auto& slot = _slots.at(4);
        if (!this->LoadTexture(tex_data.texture_index, gltf_data, slot)) {
            return false;
        } // if
        set_texcoord(slot, tex_data);
    } // if
    return true;
}

bool my::Material::Enable(const std::shared_ptr<my::Shader>& shader) {
    for (auto& slot : _slots) {
        shader->SetIntUniform(slot.texcoord_index_name.c_str(), slot.texcoord_index);
        shader->SetIntUniform(slot.enable_name.c_str(), slot.enable);
        if (slot.enable) {
            _texture.Bind(slot.location);
        } // if
    } // for
    return true;
}