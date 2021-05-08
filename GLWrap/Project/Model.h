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
    //! 名前
    std::string _name;
    //! ノード
    std::vector<std::shared_ptr<my::ModelNode>> _nodes;
    //! メッシュ
    std::vector<std::shared_ptr<my::Mesh>>_meshes;
    //! マテリアル
    std::vector<std::shared_ptr<my::Material>>_materials;
    //! アニメーション
    my::KeyFrameAnimation _key_frame_animation;
    //! アニメーション
    my::SkinAnimation _skin_animation;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <returns></returns>
    bool CreateNode(my::GLTFData& gltf_data);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <returns></returns>
    bool CreateMesh(my::GLTFData& gltf_data);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <returns></returns>
    bool CreateMaterial(my::GLTFData& gltf_data);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Model();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Model();
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <returns></returns>
    bool Load(const char* path);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="shader">シェーダ</param>
    void SetShader(const std::shared_ptr<my::Shader>& shader);
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
#endif // !MY_MODEL_H