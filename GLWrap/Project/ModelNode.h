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
    //! 名前
    std::string _name;
    //! 親
    std::weak_ptr<my::ModelNode> _parent;
    //! 子
    std::vector<std::weak_ptr<my::ModelNode>>_children;
    //! 列優先
    glm::mat4 _local_transform;
    //! 移動
    glm::vec3 _translation;
    //! 回転
    glm::quat _rotation;
    //! 拡大
    glm::vec3 _scale;
    //! メッシュ
    std::weak_ptr<my::Mesh>_mesh;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ModelNode();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ModelNode();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr">ポインタ</param>
    void SetParent(const std::shared_ptr<my::ModelNode>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr">ポインタ</param>
    void SetMesh(const std::shared_ptr<my::Mesh>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="shader">シェーダ</param>
    void SetShader(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr">ポインタ</param>
    void AddChild(const std::shared_ptr<my::ModelNode>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="data"></param>
    /// <param name="index"></param>
    /// <param name="nodes"></param>
    /// <returns></returns>
    bool Initialize(const my::GLTFData& gltf_data, int index, std::vector<std::shared_ptr<my::ModelNode>>& nodes);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>グローバルトランスフォーム</returns>
    glm::mat4 ConputeGlobalTransform(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="position"></param>
    /// <param name="rotate"></param>
    /// <param name="scale"></param>
    /// <param name="view"></param>
    /// <param name="proj"></param>
    /// <returns></returns>
    bool Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="transform"></param>
    /// <param name="view"></param>
    /// <param name="proj"></param>
    /// <returns></returns>
    bool Render(glm::mat4 transform, glm::mat4 view, glm::mat4 proj);
};
}
#endif // !MY_MODEL_NODE_H