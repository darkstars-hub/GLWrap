#ifndef MY_KEY_FRAME_ANIMATION_H
#define MY_KEY_FRAME_ANIMATION_H


#include <memory>
#include <string>
#include <vector>
#include <unordered_map>


#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#include "GLTFData.h"
#include "ModelNode.h"


namespace my {
class KeyFrameAnimation {
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
        //! �d��
        std::vector<std::vector<float>> weights;
    };

    struct WeightData {
        float weight;
        std::vector<glm::vec3> positions;
    };
    struct WeightParam{
        std::vector<WeightData>datas;
    };
    struct Weights {
        std::array<float, 8>weights;
    };
private:
    //! �A�j���[�V����
    std::vector<std::shared_ptr<AnimDataPair>> _animations;
    //! ����
    //float _current_time;
    //! �C���f�b�N�X
    uint32_t _current_animation_index;
    //! �p�����[�^
    WeightParam _param;
    //! ���[�t
    GLuint _morph_handle;

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    KeyFrameAnimation();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~KeyFrameAnimation();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <param name="nodes"></param>
    /// <returns></returns>
    bool Initialize(my::GLTFData& gltf_data, std::vector<std::shared_ptr< my::ModelNode>>& nodes);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
    /// <summary>
    /// �A�j���[�V�����s��
    /// </summary>
    /// <param name="target"></param>
    /// <returns></returns>
    glm::mat4 ConputeAnimationTransform(std::shared_ptr< my::ModelNode>& target);
    /// <summary>
    /// �쐬
    /// </summary>
    void GenerateUniform(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// �o�C���h
    /// </summary>
    void BindUniform(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// �A�j���[�V�����ύX
    /// </summary>
    /// <param name="index"></param>
    void ChangeAnimation(uint32_t index);
};
}
#endif // !MY_KEY_FRAME_ANIMATION_H