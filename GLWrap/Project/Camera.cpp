#include "Camera.h"

#include "Header.h"
#include "Helper.h"
#include "InputManager.h"
#include "Application.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/common.hpp"
#include "glm/matrix.hpp"
#include "glm/fwd.hpp"
#include "glm/exponential.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/packing.hpp"
#include "glm/simd/common.h"
#include "glm/ext/vector_common.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtx/extend.hpp"


void my::Camera::LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    _view_matrix = glm::lookAt(
        eye,
        center,
        up);
}
void my::Camera::UpdateOrtho(void) {
    _position = glm::vec3(0.0f, 0.0f, 1.0f);
    _target = glm::vec3(0.0f, 0.0f, 0.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);
    // ビュー
    _view_matrix = glm::lookAt(
        _position,
        _target,
        _up);
    // 射影
    _projection_matrix = glm::ortho(
        0.0f,
        my::kWindowWidthF,
        my::kWindowHeightF,
        0.0f,
        -1.0f,
        1.1f);
    _view_projection = _projection_matrix * _view_matrix;
}

void my::Camera::UpdatePerspective(void) {
    _up = glm::vec3(0.0f, 1.0f, 0.0f);
    // ビュー
    _view_matrix = glm::lookAt(
        _position,
        _target,
        _up);
    // 射影
    _projection_matrix = glm::perspective(
        _fovy,
        _aspect,
        _near,
        _far);
    _view_projection = _projection_matrix * _view_matrix;
}

my::Camera::Camera() :
    _fovy(::glm::radians(45.0f)),
    _aspect(my::kWindowWidthF / my::kWindowHeightF),
    _near(0.1f),
    _far(5000.0f),
    _position(),
    _target(),
    _up(def::kUnitY),
    _view_matrix(),
    _projection_matrix(),
    _view_projection() {
}
my::Camera::~Camera() {
}

void my::Camera::SetPosition(glm::vec3 pos) {
    this->_position = pos;
}

void my::Camera::SetTarget(glm::vec3 pos) {
    this->_target = pos;
}

glm::vec3 my::Camera::GetPosition(void) const {
    return this->_position;
}

glm::vec3 my::Camera::GetCameraRight(void) const {
    auto direction = glm::normalize(_position - _target);
    return glm::normalize(glm::cross(_up, direction));
}

glm::vec3 my::Camera::GetCameraUp(void) const {
    auto direction = glm::normalize(_position - _target);
    return glm::cross(direction, this->GetCameraRight());;
}

glm::mat4 my::Camera::GetViewMatrix(void) const {
    return _view_matrix;
}

glm::mat4 my::Camera::GetProjectionMatrix(void) const {
    return _projection_matrix;
}

glm::mat4 my::Camera::GetViewProjectionMatrix(void) const {
    return _view_projection;
}

inline void Rotate(float& pos_x, float& pos_y, const float angle,
                   const float center_x, const float center_y) {
    float rad = def::kPi * angle / 180.0f;

    float axis_x = pos_x - center_x;
    float axis_y = pos_y - center_y;

    float translate_x = (axis_x)*std::cosf(rad) - (axis_y)*std::sinf(rad);
    float translate_y = (axis_x)*std::sinf(rad) + (axis_y)*std::cosf(rad);

    pos_x = center_x + translate_x;
    pos_y = center_y + translate_y;
};
void my::Camera::DebugMoveByMouse(void) {
    static float vertical_angle = 0.0f;
    static float horizontal_angle = 3.14f;
    static float speed = 3.0f;
    static float mouse_speed = 0.05f;
    auto delta_time = ::g_pClock->GetDeltaTime();
    auto center = glm::vec2(my::kWindowWidthF * 0.5f, my::kWindowHeightF * 0.5f);

    auto mouse_pos = ::g_pMouse->GetMousePosition();
    ::g_pMouse->SetCursorPosition(center);
    horizontal_angle += mouse_speed * delta_time * float(center.x - mouse_pos.x);
    vertical_angle += mouse_speed * delta_time * float(center.y - mouse_pos.y);

    glm::vec3 direction = glm::vec3(
        std::cos(vertical_angle) * std::sin(horizontal_angle),
        std::sin(vertical_angle),
        std::cos(vertical_angle) * std::cos(horizontal_angle));
    glm::vec3 right = glm::vec3(
        std::sin(horizontal_angle - std::numbers::pi / 2.0f),
        0.0f,
        std::cos(horizontal_angle - std::numbers::pi / 2.0f)
    );
    glm::vec3 up = glm::cross(right, direction);

    auto key = ::g_pKeyboard;
    if (key->IsHold(my::KeyCode::Up)) {
        _position += direction * delta_time * speed;
    } // if
    if (key->IsHold(my::KeyCode::Down)) {
        _position -= direction * delta_time * speed;
    } // if
    if (key->IsHold(my::KeyCode::Left)) {
        _position -= right * delta_time * speed;
    } // if
    if (key->IsHold(my::KeyCode::Right)) {
        _position += right * delta_time * speed;
    } // if
    _view_matrix = glm::lookAt(
        _position, _position + direction, up
    );

    _fovy = _fovy - ::g_pMouse->GetMouseScroll().y * delta_time;
}

void my::Camera::DebugMoveTurn(glm::vec3 object_position, float radius, float height) {
    static float time = 0.0f;
    time += ::g_pClock->GetDeltaTime() * 0.001f;

    _position = object_position +
        glm::vec3(radius * std::cos(time), height, radius * std::sin(time));
    _view_matrix = glm::lookAt(
        _position, _target, _up
    );

}

void my::Camera::DebugMove(void) {
    if (::g_pGamepad->IsHold(my::GamepadButton::DPadLeft)) {
        // 視線ベクトルを回転させ　視点位置に加算
        glm::vec3 angle = -glm::vec3(0.0f, 0.01f, 0.0f);
        auto v = glm::rotate(glm::quat(angle), _position - _target);
        _position = _target + v;
        this->LookAt(_position, _target, def::kUnitY);
    } // if
    else if (::g_pGamepad->IsHold(my::GamepadButton::DPadRight)) {
        // 視線ベクトルを回転させ　視点位置に加算
        glm::vec3 angle = glm::vec3(0.0f, 0.01f, 0.0f);
        auto v = glm::rotate(glm::quat(angle), _position - _target);
        _position = _target + v;
        this->LookAt(_position, _target, def::kUnitY);
    } // else if
    if (::g_pGamepad->IsHold(my::GamepadButton::DPadUp)) {
        float angle = -0.01f;
        glm::vec3 v = _position - _target;
        float d = sqrt(v.x * v.x + v.z * v.z);
        float sina = std::sinf(angle);
        float cosa = std::cosf(angle);
        float tmpy = v.y * cosa + d * -sina;
        float tmpxz = v.y * sina + d * cosa;
        v.y = tmpy;
        v.x = (v.x / d) * tmpxz;
        v.z = (v.z / d) * tmpxz;
        _position = _target + v;
        this->LookAt(_position, _target, def::kUnitY);
    }
    else if (::g_pGamepad->IsHold(my::GamepadButton::DPadDown)) {
        float angle = 0.01f;
        glm::vec3 v = _position - _target;
        float d = sqrt(v.x * v.x + v.z * v.z);
        float sina = std::sinf(angle);
        float cosa = std::cosf(angle);
        float tmpy = v.y * cosa + d * -sina;
        float tmpxz = v.y * sina + d * cosa;
        v.y = tmpy;
        v.x = (v.x / d) * tmpxz;
        v.z = (v.z / d) * tmpxz;
        _position = _target + v;
        this->LookAt(_position, _target, def::kUnitY);
    }
    /*
    //ホイールによるカメラのズーム調整
    if (mv.z != 0) {
        glm::vec3 vv = _position - _target;
        vv *= 1.0f - mv.z * 0.0001f;
        _position = _target + vv;
        this->LookAt(_position, _target, def::kUnitY(0, 1, 0));
        gCamera.Update();
    }
    else if (g_pInput->IsMouseKeyHold(2)) {
        glm::vec3 vv = _position - _target;
        vv *= 1.0f + mv.y * 0.01f;
        _position = _target + vv;
        gCamera.LookAt(_position, _target, def::kUnitY(0, 1, 0));
        gCamera.Update();
    }
    //左クリックによるカメラ移動
    if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON)) {
        glm::vec3 sv;
        glm::vec3 uv;
        glm::vec3 vv = _target - _position;
        vv.Normal(vv);
        vv.Cross(gCUp, sv);
        sv.Normal(sv);
        _position += sv * mv.x * 0.01f;
        _target += sv * mv.x * 0.01f;
        sv.Cross(vv, uv);
        uv.Normal(uv);
        _position += uv * mv.y * 0.01f;
        _target += uv * mv.y * 0.01f;
        gCamera.LookAt(_position, _target, def::kUnitY(0, 1, 0));
        gCamera.Update();
    }
    //右クリックによるカメラ回転
    if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON)) {
        glm::vec3 vv = _position - _target;
        vv.RotationY(mv.x * 0.01f);
        float d = sqrt(vv.x * vv.x + vv.z * vv.z);
        float sina = std::sinf(-mv.y * 0.01f);
        float cosa = std::cosf(-mv.y * 0.01f);
        float tmpy = vv.y * cosa + d * -sina;
        float tmpxz = vv.y * sina + d * cosa;
        vv.y = tmpy;
        vv.x = (vv.x / d) * tmpxz;
        vv.z = (vv.z / d) * tmpxz;
        _position = _target + vv;
        gCamera.LookAt(_position, _target, def::kUnitY(0, 1, 0));
        gCamera.Update();
    }
    */
}

void my::Camera::Update(void) {
//    this->UpdateOrtho();
    this->UpdatePerspective();
}