#include "Window.h"

#include "Helper.h"


my::Window::Window() :
    _handle(){
}

my::Window::~Window() {
}

::GLFWwindow* my::Window::GetHandle(void) {
    return this->_handle;
}

glm::uvec2 my::Window::GetSize(void) const {
    return this->_size;
}

bool my::Window::Create(void) {
    // çÏê¨
    _handle = ::glfwCreateWindow(my::kWindowWidth,
                                 my::kWindowHeight,
                                 my::kWindowTitle,
                                 nullptr,
                                 nullptr);
    ::glfwGetWindowSize(_handle, reinterpret_cast<int*>(&_size.x), reinterpret_cast<int*>(&_size.y));

    if (!_handle) {
        ::glfwTerminate();
        return false;
    } // if
    ::glfwSetWindowPos(_handle,
                       my::kWindowPositionX,
                       my::kWindowPositionY);
    ::glfwMakeContextCurrent(_handle);
    return true;
}

void my::Window::Destroy(void) {
    ::glfwDestroyWindow(_handle);
}

bool my::Window::ShouldClose(void) const {
    return ::glfwWindowShouldClose(_handle) != 0;
}

void my::Window::Present(void) const {
    ::glfwSwapBuffers(_handle);
    ::glfwPollEvents();
}