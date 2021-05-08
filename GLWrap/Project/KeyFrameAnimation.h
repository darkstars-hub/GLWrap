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
        //! 重み
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
    //! アニメーション
    std::vector<std::shared_ptr<AnimDataPair>> _animations;
    //! 時間
    //float _current_time;
    //! インデックス
    uint32_t _current_animation_index;
    //! パラメータ
    WeightParam _param;
    //! モーフ
    GLuint _morph_handle;

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    KeyFrameAnimation();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~KeyFrameAnimation();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <param name="nodes"></param>
    /// <returns></returns>
    bool Initialize(my::GLTFData& gltf_data, std::vector<std::shared_ptr< my::ModelNode>>& nodes);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
    /// <summary>
    /// アニメーション行列
    /// </summary>
    /// <param name="target"></param>
    /// <returns></returns>
    glm::mat4 ConputeAnimationTransform(std::shared_ptr< my::ModelNode>& target);
    /// <summary>
    /// 作成
    /// </summary>
    void GenerateUniform(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// バインド
    /// </summary>
    void BindUniform(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// アニメーション変更
    /// </summary>
    /// <param name="index"></param>
    void ChangeAnimation(uint32_t index);
};
}
#endif // !MY_KEY_FRAME_ANIMATION_H