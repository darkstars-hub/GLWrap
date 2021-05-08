#include "Font.h"


my::Font::Font()
    : _font(),
    _characters(),
    _shader(),
    _vertex_array() {
}

my::Font::~Font() {
}

void my::Font::SetShader(const std::shared_ptr<my::Shader>& ptr) {
    this->_shader = ptr;
}

bool my::Font::Load(const char* path) {
    FT_Face face;
    if (::FT_Init_FreeType(&_font)) {
        return false;
    } // if
    if (::FT_New_Face(_font, path, 0, &face)) {
        return false;
    } // if
    if (::FT_Set_Pixel_Sizes(face, 128, 128)) {
        return false;
    } // if
    // •¶Žš
    ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    uint32_t ascii = 128;
    for (uint32_t code = 0; code < ascii; code++) {
        if (FT_Load_Char(face, code, FT_LOAD_RENDER)) {
            continue;
        } // if
        auto chara = Character();

        chara.texture.GenerateTexture(1);
        chara.texture.Bind();
        ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                       face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED,
                       GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


        chara.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        chara.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        chara.advance = static_cast<unsigned int>(face->glyph->advance.x);
        _characters.insert(std::pair<char, Character>(code, chara));
    }
    ::FT_Done_Face(face);
    ::FT_Done_FreeType(_font);

    // ’¸“_
    std::vector<my::FontVertex> vertices;
    vertices.resize(4);
    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };
    _vertex_array = my::VertexArray<my::FontVertex>(vertices, indices);
    _vertex_array.Generate(GL_DYNAMIC_DRAW);

    return true;
}

bool my::Font::Render(std::string text, glm::vec2 pos, float scale, glm::vec3 color, glm::vec2 window_size) {
    if (_shader.expired()) {
        return false;
    } // if

    glm::mat4 proj = glm::ortho(0.0f, window_size.x, 0.0f, window_size.y);
    auto shader = _shader.lock();
    shader->Enable();
    shader->SetVector3Uniform("text_color", color);
    shader->SetMatrixUniform("proj", proj);

    _vertex_array.Bind();
    for (auto it = text.begin(); it != text.end(); it++) {
        auto& chara = _characters.at(*it);

        float x = pos.x + chara.bearing.x * scale;
        float y = pos.y - (chara.size.y - chara.bearing.y) * scale;
        float w = chara.size.x * scale;
        float h = chara.size.y * scale;

        auto vertices = std::vector<my::FontVertex>();
        vertices.push_back(my::FontVertex(glm::vec2(x, y + h), glm::vec2(0.0f, 0.0f)));
        vertices.push_back(my::FontVertex(glm::vec2(x, y), glm::vec2(0.0f, 1.0f)));
        vertices.push_back(my::FontVertex(glm::vec2(x + w, y), glm::vec2(1.0f, 1.0f)));
        vertices.push_back(my::FontVertex(glm::vec2(x + w, y + h), glm::vec2(1.0f, 0.0f)));

        chara.texture.Bind();
        _vertex_array.Update(vertices);
        _vertex_array.Render();

        pos.x += (chara.advance >> 6) * scale;
    } // for
    return true;
}