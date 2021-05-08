#ifndef MY_MODEL_NODE_H
#define MY_MODEL_NODE_H


#include <memory>
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "GLTFData.h"
#include "Shader.h"
#include "Mesh.h"


namespace my {
class ModelNode : std::enable_shared_from_this<my::ModelNode> {
private:
    //! ���O
    std::string _name;
    //! �e
    std::weak_ptr<my::ModelNode> _parent;
    //! �q
    std::vector<std::weak_ptr<my::ModelNode>>_children;
    //! ��D��
    glm::mat4 _local_transform;
    //! �ړ�
    glm::vec3 _translation;
    //! ��]
    glm::quat _rotation;
    //! �g��
    glm::vec3 _scale;
    //! ���b�V��
    std::weak_ptr<my::Mesh>_mesh;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ModelNode();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ModelNode();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr">�|�C���^</param>
    void SetParent(const std::shared_ptr<my::ModelNode>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr">�|�C���^</param>
    void SetMesh(const std::shared_ptr<my::Mesh>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="shader">�V�F�[�_</param>
    void SetShader(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr">�|�C���^</param>
    void AddChild(const std::shared_ptr<my::ModelNode>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="data"></param>
    /// <param name="index"></param>
    /// <param name="nodes"></param>
    /// <returns></returns>
    bool Initialize(const my::GLTFData& gltf_data, int index, std::vector<std::shared_ptr<my::ModelNode>>& nodes);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�O���[�o���g�����X�t�H�[��</returns>
    glm::mat4 ConputeGlobalTransform(void);
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
#endif // !MY_MODEL_NODE_H