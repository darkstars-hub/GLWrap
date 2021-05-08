#ifndef MY_HELPER_H
#define MY_HELPER_H


#include <assert.h>

#include <type_traits>
#include <memory>
#include <string>
#include <random>
#include <numbers>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>


#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "rapidjson/document.h"


namespace def {
constexpr float kPi = static_cast<float>(std::numbers::pi);
//! 単位ベクトル
constexpr glm::vec3 kZeroVector3 = glm::vec3(0.0f);
constexpr glm::vec3 kUnitVector3 = glm::vec3(1.0f);
constexpr glm::vec3 kUnitX = glm::vec3(1.0f, 0.0f, 0.0f);
constexpr glm::vec3 kUnitY = glm::vec3(0.0f, 1.0f, 0.0f);
constexpr glm::vec3 kUnitZ = glm::vec3(0.0f, 0.0f, 1.0f);
//constexpr glm::mat4 kIdentityMatrix = glm::mat4(1.0f);
//constexpr glm::quat kDefaultQuaternion = glm::quat();
}
namespace ut {
template <class... Args>
auto CountArguments(Args... args) {
    return sizeof...(args);
}
template<class... Args>
auto Sum(Args... args) {
    return (args + ...);
}
template<class... Args>
auto Average(Args... args) {
    return (args + ...) / CountArguments(args...);
}
template<class To, class From>
To lexical_cast(From from) {
    To result;
    std::stringstream ss;
    ss << from;
    ss >> result;
    return result;
}
template<class T>
void VectorTranspose(std::vector<std::vector<T>>& source, std::vector<std::vector<T>>& destination) {
    uint32_t row_size = source.size();
    uint32_t col_size = source.at(0).size();

    destination.resize(col_size);
    for (auto& v : destination) {
        v.resize(row_size);
    } // for


    for (uint32_t i = 0; i < row_size; ++i) {
        for (uint32_t j = 0; j < col_size; ++j) {
            destination.at(j).at(i) = source.at(i).at(j);
        } // for
    } // for
}
static void IOSetting(void) {
    std::cout << std::fixed << std::setprecision(7) << std::boolalpha;
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
static int GenerateRandom(const int min, const int max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> random(min, max);
    return random(engine);
}
static float GenerateRandomF(const float min, const float max) {
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_real_distribution<> random(min, max);
    return static_cast<float>(random(engine));
}

static bool ParseJsonDocument(const char* path, rapidjson::Document& document) {
    std::ifstream file(path);
    // ファイルを開けないならfalseを返す
    if (!file.is_open()) {
        return false;
    } // if
    // 読み込み
    std::stringstream stream;
    stream << file.rdbuf();
    std::string temp = stream.str();
    rapidjson::StringStream str(temp.c_str());
    document.ParseStream(str);
    return true;
}


}
namespace ty {
/// <summary>
/// 引数を分ける
/// </summary>
/// <typeparam name="Head"></typeparam>
/// <typeparam name="...Tail"></typeparam>
template<class Head, class...Tail>
struct ArgSeparator {
    typedef Head head;
    typedef std::tuple<Tail...> tail;
};
template<class...Args>
struct ArgList {
    typedef typename ArgSeparator<Args...>::head head;
    typedef typename ArgSeparator<Args...>::tail tail;
};


template<class T>
struct is_shared : std::false_type {
};
template<class T>
struct is_shared<std::shared_ptr<T>> : std::true_type {
};
template<class T>
struct remove_shared {
    typedef T type;
};
template<class T>
struct remove_shared<std::shared_ptr<T>> {
    typedef T type;
};

/// <summary>
/// タプルのインデックス
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="Tuple"></typeparam>
template <typename Tuple, typename T, int i = std::tuple_size<Tuple>::value - 1>
struct tuple_index {
    static const int value = std::is_same<typename std::tuple_element<i, Tuple>::type, T>::value ?
        i :
        tuple_index<Tuple, T, i - 1>::value;
};
/// <summary>
/// タプルのインデックス
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="Tuple"></typeparam>
template <typename Tuple, typename T>
struct tuple_index<Tuple, T, -1> {
    static const int value = -1;
};

/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_initialize_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Initialize(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_initialize : public decltype(has_func_initialize_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};

/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_input_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Input(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_input : public decltype(has_func_input_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};

/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_update_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Update(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_update : public decltype(has_func_update_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};

/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_render_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Render(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_render : public decltype(has_func_render_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};

/// <summary>
/// メンバ関数を持っているか
/// </summary>
struct has_func_release_impl {
    template <class T, class...Args>
    static auto check(T&& x, Args&&...args)->decltype(x.Release(args...), std::true_type{});
    template <class T>
    static auto check(...)->std::false_type;
};
/// <summary>
/// メンバ関数を持っているか
/// </summary>
/// <typeparam name="T">型</typeparam>
template <class T, class...Args>
class has_func_release : public decltype(has_func_release_impl::check<T>(std::declval<T>(), std::forward<Args>(Args())...)) {};
}

namespace my{
constexpr const char* kWindowTitle = "Title";
constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
constexpr float kWindowWidthF = 1024.0f;
constexpr float kWindowHeightF = 768.0f;
constexpr int kWindowPositionX = 50;
constexpr int kWindowPositionY = 50;
}
#endif // !MY_HELPER_H
