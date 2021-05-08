#ifndef MY_MESH_H
#define MY_MESH_H



#include <memory>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "GLTFData.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"


namespace my {
class Mesh {
private:
    //! ���O
    std::string _name;
    //! ���_
    my::VertexArray<my::SkinVertex> _vertex_array;
    //! �V�F�[�_
    std::weak_ptr<my::Shader> _shader;
    //! �}�e���A��
    std::weak_ptr<my::Material> _material;
    //! �}�e���A��
    int _material_index;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Mesh();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Mesh();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="shader">�|�C���^</param>
    void SetShader(const std::shared_ptr<my::Shader>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr">�|�C���^</param>
    void SetMaterial(const std::shared_ptr<my::Material>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="">�C���f�b�N�X</param>
    uint32_t GetMaterialIndex(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    bool Initialize(my::GLTFData& gltf_data, int index);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="position"></param>
    /// <param name="rotate"></param>
    /// <param name="scale"></param>
    /// <param name="view"></param>
    /// <param name="proj"></param>
    /// <returns></returns>
    bool Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj);
    bool Render(glm::mat4 transform, glm::mat4 view, glm::mat4 proj);
};
}
#endif // !MY_MESH_H
