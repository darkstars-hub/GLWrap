// 使用ヘッダのインクルード


#ifndef MY_HEADER_H
#define MY_HEADER_H

/*
#include <assert.h>

#include <utility>
#include <tuple>
#include <optional>
#include <any>
#include <type_traits>
#include <functional>
#include <memory>
#include <string>
#include <array>
#include <deque>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <numbers>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
*/


#include <Windows.h>
#ifdef APIENTRY
#undef APIENTRY
#endif // APIENTRY
#ifdef max
#undef max
#endif // max
#ifdef min
#undef min
#endif // min
#include "xinput/Xinput.h"


#include "GL/glew.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include <GLFW/glfw3native.h>
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/quaternion.hpp"
//#include "../imgui/imgui.h"
//#include "../imgui/imgui_impl_glfw_gl3.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION
#include "rapidjson/document.h"


#endif // !MY_HEADER_H