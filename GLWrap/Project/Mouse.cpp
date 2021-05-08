#include "Mouse.h"

#include <algorithm>

#include "Header.h"
#include "GLFW/glfw3.h"


glm::vec2 my::Mouse::_mouse_scroll = glm::vec2();

my::Mouse::Mouse() :
    _window() {
}

my::Mouse::~Mouse() {
}

void my::Mouse::SetWindow(const std::shared_ptr<my::Window>& ptr) {
    this->_window = ptr;
    
    auto func = [](GLFWwindow* window, double x, double y) {
        my::Mouse::_mouse_scroll.x = static_cast<float>(x);
        my::Mouse::_mouse_scroll.y = static_cast<float>(y);
    };
    ::glfwSetScrollCallback(_window.lock()->GetHandle(), func);
}

void my::Mouse::SetCursorPosition(glm::vec2 position) {
    assert(!_window.expired());
    auto window = _window.lock();
    ::glfwSetCursorPos(window->GetHandle(), position.x, position.y);
}

glm::vec2 my::Mouse::GetMouseScroll(void) const {
    return my::Mouse::_mouse_scroll;
}

glm::uvec2 my::Mouse::GetMousePosition(void) {
    assert(!_window.expired());
    auto window = _window.lock();

    double x, y;
    auto size = window->GetSize();
    
    ::glfwGetCursorPos(window->GetHandle(), &x, &y);
    glm::uvec2 pos(std::clamp(static_cast<int>(x), 0, static_cast<int>(size.x)),
                   std::clamp(static_cast<int>(y), 0, static_cast<int>(size.y)));
    return pos;
}

bool my::Mouse::Refresh(void) {
    if (_window.expired()) {
        return false;
    } // if

    return true;
}

void my::Mouse::Reset(void) {
    _mouse_scroll = glm::vec2();
}