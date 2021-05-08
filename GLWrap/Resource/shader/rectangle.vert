#version 400 core


layout(location = 0) in vec3 vertex_position;

out vec4 color;

uniform vec4 uniform_color;
uniform mat4 transform;
uniform mat4 view_projection;


void main() {
    vec4 pos = vec4(vertex_position, 1.0);
    gl_Position =  pos * transform * view_projection;

	color = uniform_color;
}