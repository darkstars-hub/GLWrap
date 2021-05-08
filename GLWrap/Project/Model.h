#ifndef MY_MODEL_H
#define MY_MODEL_H


#include <string>
#include <vector>

#include "GLTFData.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "ModelNode.h"
#include "Mesh.h"
#include "Material.h"
#include "KeyFrameAnimation.h"
#include "SkinAnimation.h"


namespace my {
class Model {
private:
    //! ���O
    std::string _name;
    //! �m�[�h
    std::vector<std::shared_ptr<my::ModelNode>> _nodes;
    //! ���b�V��
    std::vector<std::shared_ptr<my::Mesh>>_meshes;
    //! �}�e���A��
    std::vector<std::shared_ptr<my::Material>>_materials;
    //! �A�j���[�V����
    my::KeyFrameAnimation _key_frame_animation;
    //! �A�j���[�V����
    my::SkinAnimation _skin_animation;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <returns></returns>
    bool CreateNode(my::GLTFData& gltf_data);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <returns></returns>
    bool CreateMesh(my::GLTFData& gltf_data);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <returns></returns>
    bool CreateMaterial(my::GLTFData& gltf_data);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Model();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Model();
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="path">�p�X</param>
    /// <returns></returns>
    bool Load(const char* path);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="shader">�V�F�[�_</param>
    void SetShader(const std::shared_ptr<my::Shader>& shader);
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
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="transform"></param>
    /// <param name="view"></param>
    /// <param name="proj"></param>
    /// <returns></returns>
    bool Render(glm::mat4 transform, glm::mat4 view, glm::mat4 proj);
};
}
#endif // !MY_MODEL_H