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
    //! 名前
    std::string _name;
    //! 頂点
    my::VertexArray<my::SkinVertex> _vertex_array;
    //! シェーダ
    std::weak_ptr<my::Shader> _shader;
    //! マテリアル
    std::weak_ptr<my::Material> _material;
    //! マテリアル
    int _material_index;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Mesh();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Mesh();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="shader">ポインタ</param>
    void SetShader(const std::shared_ptr<my::Shader>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr">ポインタ</param>
    void SetMaterial(const std::shared_ptr<my::Material>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="">インデックス</param>
    uint32_t GetMaterialIndex(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="gltf_data"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    bool Initialize(my::GLTFData& gltf_data, int index);
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
    bool Render(glm::mat4 transform, glm::mat4 view, glm::mat4 proj);
};
}
#endif // !MY_MESH_H
