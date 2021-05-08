#include "Texture.h"

#include "stb/stb_image.h"

#include "Helper.h"


my::Texture::ImageData::ImageData() :
    loaded(false),
    pixels(),
    width(0),
    height(0) {
}
my::Texture::ImageData::ImageData(int w, int h) :
    loaded(false),
    pixels(),
    width(w),
    height(h) {
}

bool my::Texture::ImageData::Load(const char* path) {
    loaded = false;
    pixels = ::stbi_load(path, &width, &height, nullptr, STBI_rgb_alpha);
    if (!pixels) {
        return loaded;
    } // if
    loaded = true;
    return loaded;
}

bool my::Texture::ImageData::Release(void) {
    if (!loaded) {
        return false;
    } // if
    ::stbi_image_free(pixels);
    loaded = false;
    return true;
}

my::Texture::Texture() :
    _size(),
    _texture_ids(),
    _name(),
    _shader(),
    _vertex_array(),
    _instancing_handle() {
}
my::Texture::~Texture() {
}

void my::Texture::SetShader(const std::shared_ptr<my::Shader>& shader) {
    this->_shader = shader;
}

GLuint my::Texture::GetID(uint32_t index) const {
    return this->_texture_ids.at(index);
}

glm::vec2 my::Texture::GetSize(void) const {
    return this->_size;
}
std::string my::Texture::GetName(void) const {
    return this->_name;
}

bool my::Texture::Load(const char* path) {
    // 読み込み
    ImageData image_data = ImageData();
    if (!image_data.Load(path)) {
        return false;
    } // if
    _size = glm::vec2(image_data.width, image_data.height);

    // テクスチャ、　コンテキストを作成したスレッドでなければ生成できない
    this->GenerateTexture(1);
    this->Bind();
    this->WriteImage(image_data);
    image_data.Release();

    this->GenerateMipMap();
    this->GenerateVertexBuffer();
    return true;
}

void my::Texture::GenerateTexture(uint32_t count) {
    if (_texture_ids.size() < count) {
        _texture_ids.resize(count);
    } // if
    ::glGenTextures(count, _texture_ids.data());
}

void my::Texture::GenerateVertexBuffer(void) {
    std::vector<my::NormalVertex> vertices;
    vertices = {
        { glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f) }, // left top
        { glm::vec3(-0.5f,-0.5f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f) }, // left bottom
        { glm::vec3(0.5f,-0.5f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f) }, // right bottom
        { glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f) }, // right top
    };
    bool ortho = 0;//true;//false;
    if (ortho) {
        for (auto& v : vertices) {
            v.position.y *= -1;
        } // for
    } // if

    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };
    _vertex_array = my::VertexArray<my::NormalVertex>(vertices, indices);
    _vertex_array.Generate();

    _vertex_array.ToTriangles();

    _vertex_array.UnBind();
}

void my::Texture::GenerateInstancingData(void) {
    _vertex_array.Bind();
    size_t size = sizeof(my::Texture::InstancedData);// *count;

    ::glGenBuffers(1, &_instancing_handle);
    ::glBindBuffer(GL_ARRAY_BUFFER, _instancing_handle);
    ::glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
    ::glBufferSubData(GL_ARRAY_BUFFER, 0, size, nullptr);

     // translate
    int translate = 3; // index
    ::glVertexAttribPointer(translate,
                            sizeof(glm::vec3) / sizeof(float),
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(my::Texture::InstancedData),
                            reinterpret_cast<GLvoid*>(offsetof(my::Texture::InstancedData, my::Texture::InstancedData::translate)));
    ::glEnableVertexAttribArray(translate);
    // rotate
    int rotate = 4; // index
    ::glVertexAttribPointer(rotate,
                            sizeof(glm::quat) / sizeof(float),
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(my::Texture::InstancedData),
                            reinterpret_cast<GLvoid*>(offsetof(my::Texture::InstancedData, my::Texture::InstancedData::rotate)));
    ::glEnableVertexAttribArray(rotate);
    // scale
    int scale = 5; // index
    ::glVertexAttribPointer(scale,
                            sizeof(glm::vec3) / sizeof(float),
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(my::Texture::InstancedData),
                            reinterpret_cast<GLvoid*>(offsetof(my::Texture::InstancedData, my::Texture::InstancedData::scale)));
    ::glEnableVertexAttribArray(scale);
    // rectangle
    int rectangle = 6; // index
    ::glVertexAttribPointer(rectangle,
                            sizeof(my::Rectangle) / sizeof(float),
                            GL_FLOAT,
                            GL_FALSE,
                            sizeof(my::Texture::InstancedData),
                            reinterpret_cast<GLvoid*>(offsetof(my::Texture::InstancedData, my::Texture::InstancedData::rectangle)));
    ::glEnableVertexAttribArray(rectangle);
    // divide
    ::glVertexAttribDivisor(0, 0); // position
    ::glVertexAttribDivisor(1, 0); // uv
    ::glVertexAttribDivisor(2, 0); // normal
    ::glVertexAttribDivisor(translate, 1);
    ::glVertexAttribDivisor(rotate, 1);
    ::glVertexAttribDivisor(scale, 1);
    ::glVertexAttribDivisor(rectangle, 1);
}

void my::Texture::Bind(uint32_t index) {
    ::glActiveTexture(GL_TEXTURE0 + index);
    ::glBindTexture(GL_TEXTURE_2D, _texture_ids.at(index));
}

void my::Texture::WriteImage(const ImageData& image) {
    ::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                   image.width, image.height, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, image.pixels);
    ::glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MAG_FILTER,
                      GL_LINEAR);
    ::glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR);
    //::glTexParameteri(GL_TEXTURE_2D,
    //                  GL_TEXTURE_WRAP_S,
    //                  GL_REPEAT);
    //::glTexParameteri(GL_TEXTURE_2D,
    //                  GL_TEXTURE_WRAP_T,
    //                  GL_REPEAT);
}

void my::Texture::WriteImage(const ImageData& image, int format) {
    ::glTexImage2D(GL_TEXTURE_2D, 0, format,
                   image.width, image.height, 0, format,
                   GL_UNSIGNED_BYTE, image.pixels);
    ::glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MAG_FILTER,
                      GL_LINEAR);
    ::glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR);
    ::glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_WRAP_S,
                      GL_REPEAT);
    ::glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_WRAP_T,
                      GL_REPEAT);
}

void my::Texture::GenerateMipMap(void) {
    ::glGenerateMipmap(GL_TEXTURE_2D);
    if (GLEW_EXT_texture_filter_anisotropic) {
        GLfloat largest;
        ::glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
        ::glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
    } // if
}

bool my::Texture::Render(glm::vec2 position, glm::mat4 view, glm::mat4 proj) {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();


    auto translation = glm::translate(glm::identity<glm::mat4>(), glm::vec3(position, 0.0f));
    auto scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(_size, 0.0f));
    auto transform = translation * scaling;
    // セット
    shader->Enable();
    shader->SetMatrixUniform("transform", transform);
    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);
    _vertex_array.Bind();
    this->Bind();
    _vertex_array.Render();
    
    _vertex_array.UnBind();

    ::glActiveTexture(GL_TEXTURE0);
    ::glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool my::Texture::Render(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::mat4 view, glm::mat4 proj, my::Rectangle* rectangle) {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    auto rect = my::Rectangle(glm::vec2(), this->GetSize());
    if (rectangle) {
        rect = *rectangle;
    } // if

    auto translation = glm::translate(glm::identity<glm::mat4>(), position);
    auto rotation = glm::toMat4(rotate);
    auto scaling = glm::scale(glm::identity<glm::mat4>(), glm::vec3(rect.GetSize(), 0.0f)) * glm::scale(glm::identity<glm::mat4>(), glm::vec3(scale));
    auto transform = translation * rotation * scaling;
    // セット
    shader->Enable();
    shader->SetVector2Uniform("uniform_size", _size);
    shader->SetVector4Uniform("uniform_rectangle", *reinterpret_cast<glm::vec4*>(&rect));
    shader->SetMatrixUniform("transform", transform);
    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);
    _vertex_array.Bind();

    this->Bind();
    _vertex_array.Render();

    _vertex_array.UnBind();

    ::glActiveTexture(GL_TEXTURE0);
    ::glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool my::Texture::Render(my::Transform world, glm::mat4 view, glm::mat4 proj, my::Rectangle* rectangle) {
    return this->Render(world.position, world.rotate, world.scale, view, proj, rectangle);
}

bool my::Texture::Render(const std::vector<my::Texture::InstancedData>& data, glm::mat4 view, glm::mat4 proj) {
    if (_shader.expired()) {
        return false;
    } // if
    auto shader = _shader.lock();

    // セット
    shader->Enable();
    shader->SetIntUniform("draw_count", data.size());
    shader->SetVector2Uniform("uniform_size", _size);
    shader->SetMatrixUniform("view", view);
    shader->SetMatrixUniform("proj", proj);

    _vertex_array.Bind();
    size_t size = sizeof(my::Texture::InstancedData) * data.size();
    ::glBindBuffer(GL_ARRAY_BUFFER, _instancing_handle);
    ::glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
    ::glBufferSubData(GL_ARRAY_BUFFER, 0, size, data.data());
    this->Bind();
    _vertex_array.RenderInstanced(data.size());

    _vertex_array.UnBind();


    ::glActiveTexture(GL_TEXTURE0);
    ::glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool my::Texture::Release(void) {
    _shader.reset();

    ::glDeleteTextures(_texture_ids.size(), _texture_ids.data());
    _vertex_array.Delete();
    return true;
}