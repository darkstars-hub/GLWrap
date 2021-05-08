#version 450 core

layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 vertex_uv;

out vec2 texcoord;

uniform mat4 proj;

void main() {
    vec4 pos = vec4(vertex_position.xy, 0.0, 1.0);
    gl_Position = proj * pos;
    texcoord= vertex_uv;
}