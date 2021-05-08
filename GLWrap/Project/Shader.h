#ifndef MY_SHADER_H
#define MY_SHADER_H


#include <unordered_map>

#include "Header.h"
#include "glm/glm.hpp"
#include "rapidjson/document.h"

#include "Helper.h"


namespace my {
struct ShaderPath {
    //! ディレクトリパス
    std::string directory_path = "../Resource/shader/";
    //! パス
    std::unordered_map<std::string, std::string> paths;
//    type {
//        Vertex, Fragment
//    };
    bool Load(const char* path) {
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return false;
        } // if

        const auto& info = document["shader"];
        for (uint32_t i = 0; i < info.Size(); i++) {
            assert(info[i].HasMember("type"));
            assert(info[i]["type"].IsString());
            assert(info[i].HasMember("path"));
            assert(info[i]["path"].IsString());
            std::string temp = info[i]["path"].GetString();
            paths.emplace(info[i]["type"].GetString(), directory_path + temp);
        } // for
        return true;
    }
};
class Shader {
private:
    bool _is_load = false;
    GLuint _vertex_id;
    GLuint _fragment_id;
    //! シェーダハンドル
    GLuint _program_handle;
    //! ユニフォームハンドル
    GLuint _uniform_handle;
    

    bool Compile(const char* path,
                 GLuint& out);
    bool Check(const GLuint id, const GLenum type);
public:
    Shader();
    ~Shader();

    GLuint GetID(void) const;

    bool Load(const char* path);
    bool Load(const char* vert_path,
              const char* frag_path);
    bool Release(void);

    bool GenerateUniformBuffer(const char* name, std::size_t size, void* data);
    bool BindUniformBuffer(const char* name, std::size_t size, void* data);
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    void Enable(void);
    void Disable(void);
    void SetIntUniform(const char* name, int value);
    void SetFloatUniform(const char* name, float value);
    void SetVector2Uniform(const char* name, glm::vec2& vector);
    void SetVector3Uniform(const char* name, glm::vec3& vector);
    void SetVector4Uniform(const char* name, glm::vec4& vector);
    void SetMatrixUniform(const char* name, glm::mat4& matrix);
};
}
#endif // !MY_SHADER_H