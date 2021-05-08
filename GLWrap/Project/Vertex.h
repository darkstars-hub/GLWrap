#ifndef MY_VERTEX_H
#define MY_VERTEX_H


#include "glm/glm.hpp"
#include "glm/matrix.hpp"

#include "Helper.h"


namespace my {
struct Transform {
    glm::vec3 position;
    glm::vec3 rotate;
//    glm::quat rotate;
    glm::vec3 scale;

    Transform() : position(), rotate(), scale(1.0f) {}
    Transform(glm::vec3 pos) : position(pos), rotate(), scale(1.0f) {}
    Transform(glm::vec3 pos, glm::vec3 rot) : position(pos), rotate(rot), scale(1.0f) {}
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca) : position(pos), rotate(rot), scale(sca) {}

    glm::mat4 Matrix(void) {
        auto translation = glm::translate(glm::identity<glm::mat4>(), position);
        auto rotation = glm::toMat4(glm::quat(rotate));
        auto scaling = glm::scale(glm::identity<glm::mat4>(), scale);
        return translation * rotation * scaling;
    }
};
struct SimpleVertex {
    glm::vec3 position;
    SimpleVertex() : position() {}
    SimpleVertex(glm::vec2 pos) : position(glm::vec3(pos, 0.0f)) {
    }
    SimpleVertex(glm::vec3 pos) : position(pos) {}
};
struct ColorVertex {
    glm::vec3 position;
    glm::vec4 color;
    ColorVertex() : position(), color(glm::vec4(1.0f)) {}
    ColorVertex(glm::vec2 pos, glm::vec4 c) : position(glm::vec3(pos, 0.0f)), color(c) {
    }
    ColorVertex(glm::vec3 pos, glm::vec4 c) : position(pos), color(c) {}
};
struct FontVertex {
    glm::vec2 position;
    glm::vec2 texcoord;
    FontVertex() : position(), texcoord() {}
    FontVertex(glm::vec2 pos, glm::vec2 uv) : position(pos), texcoord(uv) {
    }
};
struct NormalVertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    NormalVertex() : position(), uv(), normal() {}
    NormalVertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm) : position(pos), uv(tex), normal(norm) {
    }
};
struct SkinVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord0;
    glm::vec2 texcoord1;
    glm::vec2 texcoord2;
    glm::vec2 texcoord3;
    glm::vec2 texcoord4;
    glm::vec4 color;
    glm::u16vec4 joints;
    glm::vec4 weights;
    glm::vec4 tangent;
    SkinVertex() : position(), normal(), texcoord0(), texcoord1(), color(), joints(), weights(), tangent() {
    }
};
}
#endif // !MY_VERTEX_H