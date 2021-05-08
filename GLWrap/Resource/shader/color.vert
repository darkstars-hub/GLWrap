#version 400 core


layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;

out vec4 color;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

void main() {
    vec4 pos = vec4(vertex_position, 1.0);
    
    gl_Position = proj * view * transform * pos;

	color = vertex_color;
}