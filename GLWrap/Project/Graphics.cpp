#include "Graphics.h"

#include "Header.h"


my::Graphics::Graphics() {
}

my::Graphics::~Graphics() {
}

bool my::Graphics::Setup(void) {
    if (!::glfwInit()) {
        return false;
    } // if
    ::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    ::glfwWindowHint(GLFW_SAMPLES, 0);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    ::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

bool my::Graphics::Initialize(void) {
    // ägí£ã@î\èâä˙âª
    if (::glewInit() != GLEW_OK) {
        ::glfwTerminate();
        return false;
    } // if
    if (!GLEW_ARB_vertex_program) {
        return false;
    } // if
    //::glfwSwapInterval(1);
    return true;
}

bool my::Graphics::RenderStart(void) {
    return true;
}

bool my::Graphics::Release(void) {
    ::glfwTerminate();
    return true;
}
