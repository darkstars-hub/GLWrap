// エントリポイント


#ifdef _WIN64
#ifdef _DEBUG
#define MAIN_64_DEBUG
#endif // _DEBUG
#ifdef NDEBUG
#define MAIN_64_RELEASE
#endif // NDEBUG
//#endif // _WIN64
#elif defined _WIN32
//#ifdef _WIN32
#ifdef _DEBUG
#define MAIN_32_DEBUG
#pragma comment (lib, "../lib32/xinput/xinput.lib")
#pragma comment(lib, "../lib32/GL/OpenGL32.lib")
#pragma comment(lib, "../lib32/GLEW/Debug/glew32d.lib")
#pragma comment(lib, "../lib32/GLFW/Debug/glfw3.lib")
#pragma comment(lib, "../lib32/freetype/Debug/freetyped.lib")
#endif // _DEBUG
#ifdef NDEBUG
#define MAIN_32_RELEASE
#pragma comment (lib, "../lib32/xinput/xinput.lib")
#pragma comment(lib, "../lib32/GL/OpenGL32.lib")
#pragma comment(lib, "../lib32/GLEW/Release/glew32.lib")
#pragma comment(lib, "../lib32/GLFW/Release/glfw3.lib")
#pragma comment(lib, "../lib32/freetype/Release/freetype.lib")

#endif // NDEBUG
#endif // _WINXX


#include "Application.h"


//int main(int argc, char* argv[]) {
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    int result = 0;
    result = my::Application::GetInstance().Run();
    return result;
}