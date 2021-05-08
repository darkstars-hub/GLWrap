#version 450 core
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec3 translate;
layout(location = 4) in vec4 rotate;
layout(location = 5) in vec3 scale;
layout(location = 6) in vec4 rectangle; // left, top, right, bottom;


out vec2 uv;

 
uniform int draw_count;
uniform vec2 uniform_size;
uniform mat4 view;
uniform mat4 proj;


mat3 Mat3Cast(const in vec4 quat){
    mat3 Result = mat3(1.0);
    
    float qxx = quat.x * quat.x;
    float qyy = quat.y * quat.y;
    float qzz = quat.z * quat.z;
    float qxz = quat.x * quat.z;
    float qxy = quat.x * quat.y;
    float qyz = quat.y * quat.z;
    float qwx = quat.w * quat.x;
    float qwy = quat.w * quat.y;
    float qwz = quat.w * quat.z;

    Result[0][0] = float(1.0) - float(2.0) * (qyy +  qzz);
    Result[0][1] = float(2.0) * (qxy + qwz);
    Result[0][2] = float(2.0) * (qxz - qwy);
    
    Result[1][0] = float(2.0) * (qxy - qwz);
    Result[1][1] = float(1.0) - float(2.0) * (qxx +  qzz);
    Result[1][2] = float(2.0) * (qyz + qwx);
    
    Result[2][0] = float(2.0) * (qxz + qwy);
    Result[2][1] = float(2.0) * (qyz - qwx);
    Result[2][2] = float(1.0) - float(2.0) * (qxx +  qyy);

    return Result;
}

mat4 Mat4Cast(const in vec4 quat) {
	return mat4(Mat3Cast(quat));
}
mat4 ToMat4(const in vec4 quat){
    return Mat4Cast(quat);
}

mat4 TranslateMatrix(const in mat4 m, const in vec3 v) {
mat4 result = mat4(m);
result[3] = m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3];
return result;
}

mat4 ScaleMatrix(const in mat4 m, const in vec3 v){
    mat4 result;
    result[0] = m[0] * v.x;
    result[1] = m[1] * v.y;
    result[2] = m[2] * v.z;
    result[3] = m[3];
    return result;
}


void main() {
    if(draw_count > gl_InstanceIndex){
        float width = rectangle.z- rectangle.x;
        float height = rectangle.w- rectangle.y;
        vec2 size = vec2(width, height);

        vec4 pos = vec4(vertex_position, 1.0);

        mat4 identity = mat4(1.0);
        mat4 translation = TranslateMatrix(identity, translate);
        mat4 rotation = ToMat4(rotate);
        mat4 scaling = ScaleMatrix(identity, vec3(size, 0.0f)) * ScaleMatrix(identity, scale);
        mat4 world = translation * rotation * scaling;
 
        gl_Position = proj * view * world * pos;
        uv = vertex_uv;
            vec2 left_top = vec2(rectangle.x / uniform_size.x, rectangle.y / uniform_size.y);
        vec2 right_bottom = vec2(rectangle.z / uniform_size.x, rectangle.w / uniform_size.y);
        if(vertex_uv.x < left_top.x){
            uv.x = left_top.x;
        } // if
        else if(right_bottom.x < vertex_uv.x){
            uv.x = right_bottom.x;
        } // else if
        if(vertex_uv.y < left_top.y){
            uv.y = left_top.y;
        } // if
        else if(right_bottom.y < vertex_uv.y){
            uv.y = right_bottom.y;
        } // else if
    } // if
}