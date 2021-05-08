#include "Gamepad.h"


std::array<my::GamepadState, static_cast<int>(my::GamepadButton::MaxCount)>my::Gamepad::_button_state;
std::array<int, static_cast<int>(my::GamepadButton::MaxCount)> my::Gamepad::_button_info = {
        XINPUT_GAMEPAD_A,
        XINPUT_GAMEPAD_B,
        XINPUT_GAMEPAD_X,
        XINPUT_GAMEPAD_Y,
        XINPUT_GAMEPAD_DPAD_UP,
        XINPUT_GAMEPAD_DPAD_DOWN,
        XINPUT_GAMEPAD_DPAD_LEFT,
        XINPUT_GAMEPAD_DPAD_RIGHT,
        XINPUT_GAMEPAD_LEFT_SHOULDER,
        XINPUT_GAMEPAD_RIGHT_SHOULDER,
        XINPUT_GAMEPAD_LEFT_THUMB,
        XINPUT_GAMEPAD_RIGHT_THUMB,
        XINPUT_GAMEPAD_START,
        XINPUT_GAMEPAD_BACK
};
/*
std::array<int, static_cast<int>(my::GamepadButton::MaxCount)> my::Gamepad::_button_info = {
    GLFW_GAMEPAD_BUTTON_A,
    GLFW_GAMEPAD_BUTTON_B,
    GLFW_GAMEPAD_BUTTON_X,
    GLFW_GAMEPAD_BUTTON_Y,

    GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,

    GLFW_GAMEPAD_BUTTON_BACK,
    GLFW_GAMEPAD_BUTTON_START,
    GLFW_GAMEPAD_BUTTON_GUIDE,

    GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,

    GLFW_GAMEPAD_BUTTON_DPAD_UP,
    GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    GLFW_GAMEPAD_BUTTON_DPAD_LEFT,

    GLFW_GAMEPAD_BUTTON_LAST,
    GLFW_GAMEPAD_BUTTON_CROSS,
    GLFW_GAMEPAD_BUTTON_CIRCLE,
    GLFW_GAMEPAD_BUTTON_SQUARE,
    GLFW_GAMEPAD_BUTTON_TRIANGLE,
};
*/

my::Gamepad::Gamepad()
    : _state() {
}
my::Gamepad::~Gamepad() {
}

bool my::Gamepad::Refresh(void) {
    DWORD result = ::XInputGetState(0, &_state);
    if (result != ERROR_SUCCESS) {
        return false;
    } // if

    for (int i = 0; i < static_cast<int>(GamepadButton::MaxCount); i++) {
        if (_state.Gamepad.wButtons & _button_info.at(i)) {
            if (_button_state.at(i) == my::GamepadState::None ||
                _button_state.at(i) == my::GamepadState::Release) {
                _button_state.at(i) = my::GamepadState::Press;
            } // if
            else {
                _button_state.at(i) = my::GamepadState::Hold;
            } // else
        } // if 
        else {
            if (_button_state.at(i) == my::GamepadState::Hold ||
                _button_state.at(i) == my::GamepadState::Press) {
                _button_state.at(i) = my::GamepadState::Release;
            } // if
            else {
                _button_state.at(i) = my::GamepadState::None;
            } // else
        } // else
    } // for
    return true;
}

bool my::Gamepad::IsPress(const my::GamepadButton info) const {
    return _button_state.at(static_cast<int>(info)) == GamepadState::Press;
}
bool my::Gamepad::IsHold(const my::GamepadButton info) const {
    return _button_state.at(static_cast<int>(info)) == GamepadState::Hold;
}
bool my::Gamepad::IsRelease(const my::GamepadButton info) const {
    return _button_state.at(static_cast<int>(info)) == GamepadState::Release;
}
bool my::Gamepad::IsActiveLeftTrigger(void) const {
    return this->_state.Gamepad.bLeftTrigger;
}
bool my::Gamepad::IsActiveRightTrigger(void) const {
    return this->_state.Gamepad.bRightTrigger;
}
float my::Gamepad::GetLeftStickHorizontal(void) const {
    return this->_state.Gamepad.sThumbLX;
}
float my::Gamepad::GetLeftStickVertical(void) const {
    return this->_state.Gamepad.sThumbLY;
}
float my::Gamepad::GetRightStickHorizontal(void) const {
    return this->_state.Gamepad.sThumbRX;
}
float my::Gamepad::GetRightStickVertical(void) const {
    return this->_state.Gamepad.sThumbRY;
}