#ifndef MY_SKIN_ANIMATION_H
#define MY_SKIN_ANIMATION_H

#include <memory>
#include <array>


#include "glm/glm.hpp"

#include "GLTFData.h"
#include "ModelNode.h"

namespace my {
class SkinAnimation {
    using Target = std::weak_ptr<my::ModelNode>;
    struct SteletonPair {
        std::vector<glm::mat4> inverse_binds;
        std::vector<uint32_t> joints;
    };
    struct JointMatrixPalette {
        std::array<glm::mat4, 256> matrices;
    };
    struct AnimData {
        //! �^�[�Q�b�g
        std::weak_ptr<my::ModelNode> target;
        //! ����
        std::vector<float> key_frames;
        //! ����
        float start_time;
        //! ����
        float end_time;
        //! �ړ�
        std::vector<glm::vec3> translations;
        //! ��]
        std::vector<glm::quat> rotations;
        //! �g��
        std::vector<glm::vec3> scales;
    };
    struct AnimDataPair {
        //! ���O
        std::string name;
        //! ����
        float time;
        //! ����
        float start_time;
        //! ����
        float end_time;
        //! �f�[�^
        std::vector<AnimData> anims;
    };
private:
    //! �{�[��
    std::pair<Target, SteletonPair> _joint_data;
    //! �A�j���[�V����
    std::vector<std::shared_ptr<AnimDataPair>> _animations;
    //! �C���f�b�N�X
    uint32_t _current_animation_index;
    //! �s��
    JointMatrixPalette _joint_matrix;
    /// <summary>
    /// �A�j���[�V�����s��
    /// </summary>
    /// <param name="target"></param>
    /// <returns></returns>
    glm::mat4 ConputeAnimationTransform(const std::shared_ptr< my::ModelNode>& target);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SkinAnimation();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SkinAnimation();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    bool Initialize(my::GLTFData& gltf_data, std::vector<std::shared_ptr< my::ModelNode>>& nodes);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="target"></param>
    /// <returns></returns>
    bool Update(const std::shared_ptr<my::ModelNode>& target, const std::shared_ptr<my::Shader>&shader, std::vector<std::shared_ptr<my::ModelNode>>&nodes);
};
}
#endif // !MY_SKIN_ANIMATION_H