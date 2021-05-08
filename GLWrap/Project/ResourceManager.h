#ifndef MY_RESOURCE_MANAGER_H
#define MY_RESOURCE_MANAGER_H


#include <tuple>
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>

#include "AbstructContainer.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"


namespace my {
template<typename...Types>
class ResourceManager {
private:
    //! 全て読み込まれたかどうか
    bool _is_loaded;
    //! 同期地蔵用
    std::mutex _mutex;
    //! ディレクトリパス
    std::string _directry_path;
    //! コンテナ
    std::tuple<my::AbstructContainer<
        std::unordered_map,
        std::string,
        Types,
        std::hash<std::string>,
        std::equal_to<std::string>,
        std::allocator<std::pair<const std::string, Types>>>...> _resources;

    /// <summary>
    /// shared_ptrの要素追加
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    /// <param name="">パス</param>
    /// <returns>成功</returns>
    template<class T>
    bool AddSharedElement(const char* path) {
        auto ptr = std::make_shared<T>();
        if (!ptr->Load(path)) {
            ptr.reset();
            return false;
        } // if
        this->Set<std::shared_ptr<T>>(path, ptr);
        return true;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns>アドレス</returns>
    template<class T>
    my::AbstructContainer<std::unordered_map,
        std::string,
        T,
        std::hash<std::string>,
        std::equal_to<std::string>,
        std::allocator<std::pair<const std::string, T> >>&GetContainer(void) {
        constexpr int index = ty::tuple_index<std::tuple<Types...>, T>::value;
        return std::get<index>(_resources);
    }
    /// <summary>
    /// コンテナの解放
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="t"></param>
    template <size_t N = 0, typename T>
    void Release(T& t) {
        if constexpr (N < std::tuple_size<T>::value) {
            auto& x = std::get<N>(t);
            x.Release();
            this->Release<N + 1>(t);
        } // if
    }
public:
    ResourceManager() :
        _is_loaded(false),
        _mutex(),
        _directry_path("../Resource/") {
    }
    ~ResourceManager() {
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns>完了フラグ</returns>
    bool IsLoaded(void) {
        std::lock_guard<std::mutex> lock(_mutex);
        return this->_is_loaded;
    }
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Load(const char* path) {
        _is_loaded = false;

        std::ifstream stream(path);
        std::vector<std::string> paths;

        // 読み込むファイルのパスを格納
        while (stream) {
            std::string buffer;
            std::getline(stream, buffer);
            paths.push_back(buffer);
        } // while

        // 読み込む
        for (auto& temp : paths) {
            auto data_path = _directry_path + temp;

            if (auto format = std::strstr(data_path.c_str(), ".shader"); format) {
                bool success = this->AddSharedElement<my::Shader>(data_path.c_str());
            } // if
            else if (auto format = std::strstr(data_path.c_str(), ".png"); format) {
                bool success = this->AddSharedElement<my::Texture>(data_path.c_str());
            } // else if
            else if (auto format = std::strstr(data_path.c_str(), ".gltf"); format) {
                bool success = this->AddSharedElement<my::Model>(data_path.c_str());
            } // else if

        } // for
        _is_loaded = true;
        return true;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void) {
        this->Release(_resources);
        return true;
    }
    /// <summary>
    /// セット
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    /// <param name="key">キー</param>
    /// <param name="value">値</param>
    template<class T>
    bool Set(const char* key, const T& value) {
        auto& container = this->GetContainer<T>();
        return container.Add(key, value);
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <typeparam name="T">型</typeparam>
    /// <param name="key">キー</param>
    /// <returns></returns>
    template<class T>
    T Get(const char* key) {
        auto& container = this->GetContainer<T>();
        return container.Find(std::string(_directry_path + std::string(key)).c_str());
    }
};
}
#endif // !MY_RESOURCE_MANAGER_H