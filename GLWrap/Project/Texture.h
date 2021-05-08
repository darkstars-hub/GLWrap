#ifndef MY_TEXTURE_H
#define MY_TEXTURE_H


#include <memory>
#include <string>
#include <array>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


#include "VertexArray.h"
#include "Shader.h"
#include "Rectangle.h"


namespace my {
class Texture {
public:
    struct ImageData {
        bool loaded = false;
        unsigned char* pixels = nullptr;
        int width = 0;
        int height = 0;

        ImageData();
        ImageData(int w, int h);
        bool Load(const char* path);
        bool Release(void);
    };
    /// <summary>
    /// �C���X�^���V���O�f�[�^
    /// </summary>
    struct InstancedData {
        glm::vec3 translate;
        glm::quat rotate;
        glm::vec3 scale;
        my::Rectangle rectangle;
        InstancedData() :
            translate(), rotate(), scale(1.0f), rectangle() {
        }
        InstancedData(glm::vec3 trans, glm::quat rot, glm::vec3 sca, my::Rectangle rect) :
            translate(trans), rotate(rot), scale(sca), rectangle(rect) {
        }
    };
private:
    //! �T�C�Y
    glm::vec2 _size;
    //! ID
    std::vector<GLuint> _texture_ids;
    //! ���O
    std::string _name;
    //! ���_
    my::VertexArray<my::NormalVertex> _vertex_array;
    //! �V�F�[�_
    std::weak_ptr<my::Shader> _shader;
    //! �C���X�^���V���O�̃n���h��
    GLuint _instancing_handle;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Texture();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Texture();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="shader">�V�F�[�_</param>
    void SetShader(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// �n���h��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    GLuint GetID(uint32_t index = 0) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�T�C�Y</returns>
    glm::vec2 GetSize(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>���O</returns>
    std::string GetName(void) const;
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="path">�p�X</param>
    /// <returns>����</returns>
    bool Load(const char* path);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="count"></param>
    void GenerateTexture(uint32_t count);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void GenerateVertexBuffer(void);
    /// <summary>
    /// �C���X�^���V���O�f�[�^����
    /// </summary>
    /// <param name=""></param>
    void GenerateInstancingData(void);
    /// <summary>
    /// �o�C���h
    /// </summary>
    /// <param name="index"></param>
    void Bind(uint32_t index = 0);
    /// <summary>
    /// ��������
    /// </summary>
    /// <param name=""></param>
    void WriteImage(const ImageData& image);
    void WriteImage(const ImageData& image, int format);
    /// <summary>
    /// �쐬
    /// </summary>
    void GenerateMipMap(void);
    /// �`��
    /// </summary>
    /// <param name="position">�ʒu</param>
    /// <returns></returns>
    bool Render(glm::vec2 position, glm::mat4 view, glm::mat4 proj);
    bool Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj, my::Rectangle* rectangle = nullptr);
    bool Render(my::Transform world, glm::mat4 view, glm::mat4 proj, my::Rectangle* rectangle = nullptr);
    bool Render(const std::vector<my::Texture::InstancedData>& data, glm::mat4 view, glm::mat4 proj);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    bool Release(void);
};
}
#endif // !MY_TEXTURE_H