#version 450 core


layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texcoord0;
layout(location = 3) in vec2 vertex_texcoord1;
layout(location = 4) in vec2 vertex_texcoord2;
layout(location = 5) in vec2 vertex_texcoord3;
layout(location = 6) in vec2 vertex_texcoord4;
layout(location = 7) in vec4 vertex_color;
layout(location = 8) in uvec4 vertex_joints;
layout(location = 9) in vec4 vertex_weight;
layout(location = 10) in vec4 vertex_tangent;



out vec2 texcoord;
out vec2 texcoord1;
out vec2 texcoord2;
out vec2 texcoord3;
out vec2 texcoord4;
 
uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 joint_matrices[256];


uniform int morph_weight_size;
uniform Weights {
    float morph_weights[8];
};
layout(std430, binding=0) buffer MorphPosition0 {
     vec4 morph_position0 [];
};

mat4 GetSkinMatrix(void){
    //vec4 mat = 
      //  vertex_weight.x * joint_matrices[(vertex_joints.x)] + 
      //  vertex_weight.y * joint_matrices[(vertex_joints.y)] + 
      //  vertex_weight.z * joint_matrices[(vertex_joints.z)] + 
      //  vertex_weight.w * joint_matrices[(vertex_joints.w)]  ;

    mat4 mat = mat4(1.0, 0.0, 0.0, 0.0,
               0.0, 1.0, 0.0, 0.0,
               0.0, 0.0, 1.0, 0.0,
               0.0, 0.0, 0.0, 1.0);

    return mat;
}

vec3 GetMorphPosition(void) {
    if (morph_weight_size == 0) {
        return vec3(0.0, 0.0, 0.0);
    } // if

    vec3 weigted_pos0[3] = {
        vec3(0.0,0.0,0.0),
        vec3(0.0,0.0,0.0),
        vec3(-1.0,1.0,0.0),
    };
    vec3 weigted_pos1[3] = {
        vec3(0.0,0.0,0.0),
        vec3(0.0,0.0,0.0),
        vec3(1.0,1.0,0.0),
    };
    vec3 pos_vec[2][3]= {
        weigted_pos0,
        weigted_pos1
    };
    
    vec3 ret = vec3(0.0, 0.0, 0.0);
    ret += morph_position0[gl_VertexID].xyz * morph_weights[0];
    //ret += weigted_pos0[gl_VertexID] * morph_weights[0];
    ret += weigted_pos1[gl_VertexID] * morph_weights[1];


//    for(int i = 0; i < morph_weight_size; i++){
//        ret += pos_vec[i][gl_VertexID] * morph_weights[i]; 
//    } // for
    return ret;
}

void main() {
    vec3 morph_pos = vertex_position + GetMorphPosition();
    vec4 pos = vec4(morph_pos , 1.0);

 //   vec4 skinnedPos = (pos * joint_matrices[vertex_joints.x]) * vertex_weight.x;
//	skinnedPos += (pos * joint_matrices[vertex_joints.y]) * vertex_weight.y;
//	skinnedPos += (pos * joint_matrices[vertex_joints.z]) * vertex_weight.z;
//	skinnedPos += (pos * joint_matrices[vertex_joints.w]) * vertex_weight.w;
//  skinnedPos = skinnedPos * transform;
//	gl_Position = view * proj * skinnedPos ;

    //gl_Position = proj * view *  transform * GetSkinMatrix() * pos;

    gl_Position = proj * view * transform * pos;
    texcoord = vertex_texcoord0;
    texcoord1 = vertex_texcoord1;
    texcoord2 = vertex_texcoord2;
    texcoord3 = vertex_texcoord3;
    texcoord4 = vertex_texcoord4;
}