#ifndef MY_FRAME_BUFFER_H
#define MY_FRAME_BUFFER_H


#include <memory>

#include "Header.h"

#include "Shader.h"
#include "Texture.h"


namespace my {
class FrameBuffer {
private:
    //! フレームバッファ
    GLuint _frame_buffer;
    //! レンダーバッファ
    GLuint _render_buffer;
    //! サイズ
    glm::uvec2 _size;
    //! カラーアタッチメント
    my::Texture _rendered_texture;

    //my::VertexArray<my::NormalVertex> _vertex_array;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FrameBuffer();
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Generate(glm::uvec2 size);
    bool Generate(uint32_t width, uint32_t height);
    /// <summary>
    /// バインド
    /// </summary>
    /// <param name=""></param>
    void Bind(glm::uvec2 screen_pos = glm::uvec2(),  glm::uvec2* viewport_size = nullptr);
    /// <summary>
    /// デフォルトのフレームバッファのバインド
    /// </summary>
    /// <param name=""></param>
    void UnBind(void);
    /// <summary>
    /// クリア
    /// </summary>
    /// <param name="color"></param>
    void Clear(void);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    void Delete(void);
    bool TextureRender(glm::vec2 position, glm::mat4 view, glm::mat4 proj, const std::shared_ptr<my::Shader>& shader);
};
}
#endif // !MY_FRAME_BUFFER_H