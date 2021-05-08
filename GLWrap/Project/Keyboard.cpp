#include "Keyboard.h"


std::array<my::KeyState, static_cast<int>(my::KeyCode::MaxCount)>my::Keyboard::_key_status;
std::array<int, static_cast<int>(my::KeyCode::MaxCount)> my::Keyboard::_key_codes = {
    GLFW_KEY_SPACE,
    GLFW_KEY_UP,
    GLFW_KEY_DOWN,
    GLFW_KEY_RIGHT,
    GLFW_KEY_LEFT,
    GLFW_KEY_ENTER,
    GLFW_KEY_ESCAPE,
};

my::Keyboard::Keyboard() :
    _window() {
}

void my::Keyboard::SetWindow(const std::shared_ptr<my::Window>& ptr) {
    _window = ptr;
}

bool my::Keyboard::Refresh(void) {
    if (_window.expired()) {
        return false;
    } // if
    auto window = _window.lock();
    for (int i = 0; i < static_cast<int>(my::KeyCode::MaxCount); i++) {
        if (::glfwGetKey(window->GetHandle(), _key_codes.at(i))) {
            if (_key_status.at(i) == my::KeyState::None ||
                _key_status.at(i) == my::KeyState::Release) {
                _key_status.at(i) = my::KeyState::Press;
            } // if
            else {
                _key_status.at(i) = my::KeyState::Hold;
            } // else
        } // if
        else {
            if (_key_status.at(i) == my::KeyState::Hold ||
                _key_status.at(i) == my::KeyState::Press) {
                _key_status.at(i) = my::KeyState::Release;
            } // if
            else {
                _key_status.at(i) = my::KeyState::None;
            } // else
        } // else
    } // for
    return true;
}

bool my::Keyboard::IsPress(const my::KeyCode code) const {
    return _key_status.at(static_cast<int>(code)) == my::KeyState::Press;
}

bool my::Keyboard::IsHold(const my::KeyCode code) const {
    return _key_status.at(static_cast<int>(code)) == my::KeyState::Hold;
}

bool my::Keyboard::IsRelease(const my::KeyCode code) const {
    return _key_status.at(static_cast<int>(code)) == my::KeyState::Release;
}
