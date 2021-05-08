#version 450 core


in vec2 uv;
out vec4 color;

uniform sampler2D texture_sampler;

uniform BlobSettings {
  vec4 InnerColor;
  vec4 OuterColor;
  float RadiusInner;
  float RadiusOuter;
};


void main() {
	color = texture(texture_sampler, uv);
//	color = InnerColor;
}