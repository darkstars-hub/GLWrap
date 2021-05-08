#ifndef MY_TEXTURE_H
#define MY_TEXTURE_H


#include <memory>
#include <string>
#include <array>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"


#include "VertexArray.h"
#include "Shader.h"
#include "Rectangle.h"


namespace my {
class Texture {
public:
    struct ImageData {
        bool loaded = false;
        unsigned char* pixels = nullptr;
        int width = 0;
        int height = 0;

        ImageData();
        ImageData(int w, int h);
        bool Load(const char* path);
        bool Release(void);
    };
    /// <summary>
    /// インスタンシングデータ
    /// </summary>
    struct InstancedData {
        glm::vec3 translate;
        glm::quat rotate;
        glm::vec3 scale;
        my::Rectangle rectangle;
        InstancedData() :
            translate(), rotate(), scale(1.0f), rectangle() {
        }
        InstancedData(glm::vec3 trans, glm::quat rot, glm::vec3 sca, my::Rectangle rect) :
            translate(trans), rotate(rot), scale(sca), rectangle(rect) {
        }
    };
private:
    //! サイズ
    glm::vec2 _size;
    //! ID
    std::vector<GLuint> _texture_ids;
    //! 名前
    std::string _name;
    //! 頂点
    my::VertexArray<my::NormalVertex> _vertex_array;
    //! シェーダ
    std::weak_ptr<my::Shader> _shader;
    //! インスタンシングのハンドル
    GLuint _instancing_handle;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Texture();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Texture();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="shader">シェーダ</param>
    void SetShader(const std::shared_ptr<my::Shader>& shader);
    /// <summary>
    /// ハンドル
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    GLuint GetID(uint32_t index = 0) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    glm::vec2 GetSize(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>名前</returns>
    std::string GetName(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path">パス</param>
    /// <returns>成功</returns>
    bool Load(const char* path);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="count"></param>
    void GenerateTexture(uint32_t count);
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    void GenerateVertexBuffer(void);
    /// <summary>
    /// インスタンシングデータ生成
    /// </summary>
    /// <param name=""></param>
    void GenerateInstancingData(void);
    /// <summary>
    /// バインド
    /// </summary>
    /// <param name="index"></param>
    void Bind(uint32_t index = 0);
    /// <summary>
    /// 書き込み
    /// </summary>
    /// <param name=""></param>
    void WriteImage(const ImageData& image);
    void WriteImage(const ImageData& image, int format);
    /// <summary>
    /// 作成
    /// </summary>
    void GenerateMipMap(void);
    /// 描画
    /// </summary>
    /// <param name="position">位置</param>
    /// <returns></returns>
    bool Render(glm::vec2 position, glm::mat4 view, glm::mat4 proj);
    bool Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj, my::Rectangle* rectangle = nullptr);
    bool Render(my::Transform world, glm::mat4 view, glm::mat4 proj, my::Rectangle* rectangle = nullptr);
    bool Render(const std::vector<my::Texture::InstancedData>& data, glm::mat4 view, glm::mat4 proj);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    bool Release(void);
};
}
#endif // !MY_TEXTURE_H