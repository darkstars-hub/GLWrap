#ifndef MY_FONT_H
#define MY_FONT_H


#include <memory>
#include <map>

#include "Header.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "glm/glm.hpp"

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


namespace my {
class Font {
    struct Character {
        my::Texture texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        uint32_t advance;
    };
private:
    //! �t�H���g
    FT_Library _font;
    //! ����
    std::map<GLchar, Character> _characters;
    //! �V�F�[�_
    std::weak_ptr<my::Shader> _shader;
    //! ���_
    my::VertexArray<my::FontVertex>_vertex_array;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Font();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Font();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetShader(const std::shared_ptr<my::Shader>& ptr);
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="text"></param>
    /// <param name="pos">�X�N���[�����W</param>
    /// <param name="scale"></param>
    /// <param name="color"></param>
    /// <param name="window_size"></param>
    /// <returns></returns>
    bool Render(std::string text, glm::vec2 pos, float scale = 1.0f, glm::vec3 color = glm::vec3(1.0f), glm::vec2 window_size = glm::vec2(my::kWindowWidthF, my::kWindowHeightF));
};
}
#endif // !MY_FONT_H