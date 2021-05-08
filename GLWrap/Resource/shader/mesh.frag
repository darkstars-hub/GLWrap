#version 450 core


in vec2 texcoord;
in vec2 texcoord1;
in vec2 texcoord2;
in vec2 texcoord3;
in vec2 texcoord4;

out vec4 color;


uniform bool enable_base_color;
uniform bool enable_metallic_roughness_color;
uniform bool enable_normal_color;
uniform bool enable_occlusion_color;
uniform bool enable_emissive_color;
uniform int base_color_texcoord_index;
uniform int metallic_roughness_texcoord_index;
uniform int normal_texcoord_index;
uniform int occlusion_texcoord_index;
uniform int emissive_texcoord_index;

uniform sampler2D base_color_texture;
uniform sampler2D metallic_roughness_texture;
uniform sampler2D normal_texture;
uniform sampler2D occlusion_texture;
uniform sampler2D emissive_texture;


uniform SceneParam {
    vec3 camera_position;
    vec3 light_position;
};


vec2 GetTexCoord(const in int index){
    if (index == 0) {
        return texcoord;
    } // if
    else if (index == 1) {
        return texcoord1;
    } // else if
    else if (index == 2) {
        return texcoord2;
    } // else if
    else if (index == 3) {
        return texcoord3;
    } // else if
    else if (index == 4) {
        return texcoord4;
    } // else if
    return vec2(0.0, 0.0);
}

void BaseColor(void) {
    if(enable_base_color){
        vec4 base_color = texture(base_color_texture, GetTexCoord(base_color_texcoord_index));
        color = base_color;
    } // if
}
void EmissiveColor(void) {
    if (enable_emissive_color){
        vec4 emissive_color = texture(emissive_texture, 
                                      GetTexCoord(emissive_texcoord_index));
        color += emissive_color ;
    } // if
}

void main() {
    color = vec4(1.0, 1.0, 1.0, 1.0);
    
    BaseColor();
    
    EmissiveColor();    
//    color = vec4(light_position, 1.0);
}