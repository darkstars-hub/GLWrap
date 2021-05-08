#ifndef MY_MATERIAL_H
#define MY_MATERIAL_H


#include <memory>
#include <string>
#include <array>
#include <vector>

#include "GLTFData.h"
#include "Shader.h"
#include "Texture.h"


namespace my {
class Material {
    struct TextureSlot {
        std::string name;
        uint32_t location;
        std::string enable_name;
        bool enable;
        std::string texcoord_index_name;
        uint32_t texcoord_index;
        TextureSlot(const char* str, uint32_t i, const char* enable_str, const char* texcoord_str) :
            name(str), location(i), 
            enable_name(enable_str), enable(false),
            texcoord_index_name(texcoord_str), texcoord_index(0) {
        }
    };
private:
    //! ���O
    std::string _name;
    //! �e�N�X�`��
    my::Texture _texture;
    //! �o�C���h���
    std::vector<TextureSlot>_slots;
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="texture_index"></param>
    /// <param name="gltf_data"></param>
    /// <param name="out"></param>
    /// <returns></returns>
    bool LoadTexture(int texture_index, my::GLTFData& gltf_data, TextureSlot& out);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Material();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Material();
    /// <summary>
    /// �Z�b�g
    /// </summary>
    /// <param name="shader"></param>
    void SetUniformLocation(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    bool Initialize(my::GLTFData& gltf_data, int index);
    /// <summary>
    /// �L����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Enable(const std::shared_ptr<my::Shader>& shader);
};
}
#endif // !MY_MATERIAL_H