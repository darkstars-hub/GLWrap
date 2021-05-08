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
        //! ターゲット
        std::weak_ptr<my::ModelNode> target;
        //! 時間
        std::vector<float> key_frames;
        //! 時間
        float start_time;
        //! 時間
        float end_time;
        //! 移動
        std::vector<glm::vec3> translations;
        //! 回転
        std::vector<glm::quat> rotations;
        //! 拡大
        std::vector<glm::vec3> scales;
    };
    struct AnimDataPair {
        //! 名前
        std::string name;
        //! 時間
        float time;
        //! 時間
        float start_time;
        //! 時間
        float end_time;
        //! データ
        std::vector<AnimData> anims;
    };
private:
    //! ボーン
    std::pair<Target, SteletonPair> _joint_data;
    //! アニメーション
    std::vector<std::shared_ptr<AnimDataPair>> _animations;
    //! インデックス
    uint32_t _current_animation_index;
    //! 行列
    JointMatrixPalette _joint_matrix;
    /// <summary>
    /// アニメーション行列
    /// </summary>
    /// <param name="target"></param>
    /// <returns></returns>
    glm::mat4 ConputeAnimationTransform(const std::shared_ptr< my::ModelNode>& target);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SkinAnimation();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SkinAnimation();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    bool Initialize(my::GLTFData& gltf_data, std::vector<std::shared_ptr< my::ModelNode>>& nodes);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="target"></param>
    /// <returns></returns>
    bool Update(const std::shared_ptr<my::ModelNode>& target, const std::shared_ptr<my::Shader>&shader, std::vector<std::shared_ptr<my::ModelNode>>&nodes);
};
}
#endif // !MY_SKIN_ANIMATION_H