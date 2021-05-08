#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


bool my::Shader::Compile(const char* path, GLuint& out) {
    std::ifstream stream(path, std::ios::in);
    if (!stream.is_open()) {
        return false;
    } // if
    std::stringstream buffer;
    buffer << stream.rdbuf();
    auto code = buffer.str();
    stream.close();

    const char* source = code.c_str();
    ::glShaderSource(out, 1, &source, NULL);
    ::glCompileShader(out);
    return true;
}

bool my::Shader::Check(const GLuint id, const GLenum type) {
    int info_log_length;
    ::glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::string message;
        message.resize(info_log_length + 1);
        ::glGetShaderInfoLog(
            id,
            info_log_length,
            NULL,
            message.data());
        std::cout << message.data();
        return false;
    } // if
    return true;
}

my::Shader::Shader() :
    _vertex_id(0),
    _fragment_id(0),
    _program_handle(0),
    _uniform_handle() {
}

my::Shader::~Shader() {
}

GLuint my::Shader::GetID(void) const {
    return this->_program_handle;
}

bool my::Shader::Load(const char* path) {
    auto shader_path = my::ShaderPath();
    if (!shader_path.Load(path)) {
        return false;
    } // if

    auto vertex = shader_path.paths.at("Vertex").c_str();
    auto fragment = shader_path.paths.at("Fragment").c_str();
    return this->Load(vertex, fragment);
}

bool my::Shader::Load(const char* vert_path, const char* frag_path) {
    // vert
    _vertex_id = ::glCreateShader(GL_VERTEX_SHADER);
    this->Compile(vert_path, _vertex_id);
    if (!this->Check(_vertex_id, GL_COMPILE_STATUS)) {
        return false;
    } // if
    // frag
    _fragment_id = ::glCreateShader(GL_FRAGMENT_SHADER);
    this->Compile(frag_path, _fragment_id);
    if (!this->Check(_fragment_id, GL_COMPILE_STATUS)) {
        return false;
    } // if
    // 作成
    _program_handle = ::glCreateProgram();
    if (_program_handle == NULL) {
        return false;
    } // if

    ::glAttachShader(_program_handle, _vertex_id);
    ::glAttachShader(_program_handle, _fragment_id);
    ::glLinkProgram(_program_handle);
    // 片付け
    ::glDetachShader(_program_handle, _vertex_id);
    ::glDetachShader(_program_handle, _fragment_id);
    ::glDeleteShader(_vertex_id);
    ::glDeleteShader(_fragment_id);
    _vertex_id = NULL;
    _fragment_id = NULL;
    _is_load = true;
    return true;
}

bool my::Shader::Release(void) {
    ::glDeleteProgram(_program_handle);
    return true;
}

bool my::Shader::GenerateUniformBuffer(const char* name, std::size_t size, void* data) {
    GLuint block_index = ::glGetUniformBlockIndex(_program_handle, name);
    // create buffer
    ::glGenBuffers(1, &_uniform_handle);
    ::glBindBuffer(GL_UNIFORM_BUFFER, _uniform_handle);
    ::glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
    // bind
    ::glBindBufferBase(GL_UNIFORM_BUFFER, block_index, _uniform_handle);
    return true;
}

bool my::Shader::BindUniformBuffer(const char* name, std::size_t size, void* data) {
    GLuint block_index = ::glGetUniformBlockIndex(_program_handle, name);
    ::glBindBuffer(GL_UNIFORM_BUFFER, _uniform_handle);
    ::glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
    // bind
    ::glBindBufferBase(GL_UNIFORM_BUFFER, block_index, _uniform_handle);
    return true;
}

void my::Shader::Enable(void) {
#ifdef _DEBUG
    _ASSERT_EXPR(_is_load,
                 L"シェーダが読み込まれていません");
#endif // _DEBUG
    ::glUseProgram(_program_handle);
}

void my::Shader::Disable(void) {
    ::glUseProgram(0);
}

void my::Shader::SetIntUniform(const char* name, int value) {
    auto location = ::glGetUniformLocation(
        _program_handle, name);
    ::glUniform1i(location,
                  value);
}

void my::Shader::SetFloatUniform(const char* name, float value) {
    auto location = ::glGetUniformLocation(
        _program_handle, name);
    ::glUniform1f(location,
                  value);
}

void my::Shader::SetVector2Uniform(const char* name, glm::vec2& vector) {
    auto location = ::glGetUniformLocation(
        _program_handle, name);
    ::glUniform2fv(location,
                   1,
                   reinterpret_cast<float*>(&vector));
}

void my::Shader::SetVector3Uniform(const char* name, glm::vec3& vector) {
    auto location = ::glGetUniformLocation(
        _program_handle, name);
    ::glUniform3fv(location,
                   1,
                   reinterpret_cast<float*>(&vector));
}

void my::Shader::SetVector4Uniform(const char* name, glm::vec4& vector) {
    auto location = ::glGetUniformLocation(
        _program_handle, name);
    ::glUniform4fv(location,
                   1,
                   reinterpret_cast<float*>(&vector));
}

void my::Shader::SetMatrixUniform(const char* name, glm::mat4& matrix) {
    auto location = ::glGetUniformLocation(
        _program_handle, name);
    ::glUniformMatrix4fv(location,
                         1,
//                         GL_TRUE,
                         GL_FALSE,
                         reinterpret_cast<float*>(&matrix));
}

/*
void my::Shader::SetMatrixUniforms(
    const char* name,
    std::array<glm::mat4, my::kBoneCountMax>& matrices) {
    auto location = ::glGetUniformLocation(
        _program_handle, name);
    ::glUniformMatrix4fv(location,
                         matrices.size(),
                         GL_TRUE,
                         &matrices[0][0][0]);
}
*/