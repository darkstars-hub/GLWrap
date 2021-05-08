#ifndef MY_FRAME_BUFFER_H
#define MY_FRAME_BUFFER_H


#include <memory>

#include "Header.h"

#include "Shader.h"
#include "Texture.h"


namespace my {
class FrameBuffer {
private:
    //! �t���[���o�b�t�@
    GLuint _frame_buffer;
    //! �����_�[�o�b�t�@
    GLuint _render_buffer;
    //! �T�C�Y
    glm::uvec2 _size;
    //! �J���[�A�^�b�`�����g
    my::Texture _rendered_texture;

    //my::VertexArray<my::NormalVertex> _vertex_array;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FrameBuffer();
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Generate(glm::uvec2 size);
    bool Generate(uint32_t width, uint32_t height);
    /// <summary>
    /// �o�C���h
    /// </summary>
    /// <param name=""></param>
    void Bind(glm::uvec2 screen_pos = glm::uvec2(),  glm::uvec2* viewport_size = nullptr);
    /// <summary>
    /// �f�t�H���g�̃t���[���o�b�t�@�̃o�C���h
    /// </summary>
    /// <param name=""></param>
    void UnBind(void);
    /// <summary>
    /// �N���A
    /// </summary>
    /// <param name="color"></param>
    void Clear(void);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name=""></param>
    void Delete(void);
    bool TextureRender(glm::vec2 position, glm::mat4 view, glm::mat4 proj, const std::shared_ptr<my::Shader>& shader);
};
}
#endif // !MY_FRAME_BUFFER_H