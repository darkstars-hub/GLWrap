#ifndef MY_ABSTRACT_CONTAINER_H
#define MY_ABSTRACT_CONTAINER_H


#include <type_traits>
#include <functional>
#include <vector>
#include <unordered_map>

#include "Helper.h"


namespace my {
template<template<class...> class Container, class...Args>
class AbstructContainer {
    using Type = typename ty::ArgSeparator<Args...>::head;
private:
    //! コンテナ
    Container<Args...> _elements;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AbstructContainer() : _elements() {
    }
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="ptr"></param>
    AbstructContainer(std::pmr::memory_resource* ptr) : _elements(Container<Type>(ptr)) {
    }
    /// <summary>
    /// begin
    /// </summary>
    /// <returns></returns>
    Type* begin(void) {
        return &_elements[0];
    }
    /// <summary>
    /// end
    /// </summary>
    /// <returns></returns>
    Type* end(void) {
        return begin() + _elements.size();
    }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="value">値</param>
    void Add(const Type& value) {
        _elements.push_back(value);
    }
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="value"></param>
    /// <returns>値</returns>
    void Remove(const Type& value) {
        _elements.erase(
            std::remove(_elements.begin(), _elements.end(), value),
            _elements.end());
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="value">値</param>
    /// <returns>保持していればtrueを返す</returns>
    bool Exist(const Type& value) {
        auto it = std::find(_elements.begin(), _elements.end(), value);
        if (it != _elements.end()) {
            return true;
        } // if
        return false;
    }
    /// <summary>
    /// 取得
    /// </summary>
    /// <param name="lambda">条件</param>
    /// <returns></returns>
    Type Find(std::function<bool(const Type&)> lambda) {
        auto it = std::find_if(_elements.begin(), _elements.end(), lambda);
        if (it != _elements.end()) {
            return *it;
        } // if
        if constexpr (std::is_pointer<Type>::value) {
            return nullptr;
        } // if
        return Type();
    }
    /// <summary>
    /// 初期化
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Initialize(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Type>::type;
        using RemovedPtr = typename std::remove_pointer<Type>::type;
        using T = typename std::conditional<ty::is_shared<Type>::value, RemovedShared,
            std::conditional<std::is_pointer<Type>::value, RemovedPtr, Type>::type>::type;

        if constexpr (ty::has_func_initialize<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Type>::value || ty::is_shared<Type>::value) {
                for (auto& elem : _elements) {
                    elem->Initialize(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.Initialize(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 入力
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Input(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Type>::type;
        using RemovedPtr = typename std::remove_pointer<Type>::type;
        using T = typename std::conditional<ty::is_shared<Type>::value, RemovedShared,
            std::conditional<std::is_pointer<Type>::value, RemovedPtr, Type>::type>::type;

        if constexpr (ty::has_func_input<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Type>::value || ty::is_shared<Type>::value) {
                for (auto& elem : _elements) {
                    elem->Input(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.Input(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 更新
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Update(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Type>::type;
        using RemovedPtr = typename std::remove_pointer<Type>::type;
        using T = typename std::conditional<ty::is_shared<Type>::value, RemovedShared,
            std::conditional<std::is_pointer<Type>::value, RemovedPtr, Type>::type>::type;

        if constexpr (ty::has_func_update<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Type>::value || ty::is_shared<Type>::value) {
                for (auto& elem : _elements) {
                    elem->Update(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.Update(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Render(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Type>::type;
        using RemovedPtr = typename std::remove_pointer<Type>::type;
        using T = typename std::conditional<ty::is_shared<Type>::value, RemovedShared,
            std::conditional<std::is_pointer<Type>::value, RemovedPtr, Type>::type>::type;

        if constexpr (ty::has_func_render<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Type>::value || ty::is_shared<Type>::value) {
                for (auto& elem : _elements) {
                    elem->Render(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.Render(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Release(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Type>::type;
        using RemovedPtr = typename std::remove_pointer<Type>::type;
        using T = typename std::conditional<ty::is_shared<Type>::value, RemovedShared,
            std::conditional<std::is_pointer<Type>::value, RemovedPtr, Type>::type>::type;

        if constexpr (ty::has_func_release<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Type>::value || ty::is_shared<Type>::value) {
                for (auto& elem : _elements) {
                    elem->Release(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.Release(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }

};

template<class Key, class Value, class Hash, class Pred, class Allocator>
class AbstructContainer<std::unordered_map, Key, Value, Hash, Pred, Allocator> {
private:
    //! コンテナ
    std::unordered_map<Key, Value, Hash, Pred, Allocator> _elements;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AbstructContainer() : _elements() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~AbstructContainer() {
    }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="pair">ペア</param>
    /// <returns>成功</returns>
    bool Add(const std::pair<Key, Value>& pair) {
        if (this->Exist(pair.first)) {
            return false;
        } // if
        _elements.emplace(pair);
        return true;
    }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="key">キー</param>
    /// <param name="value">値</param>
    /// <returns>成功</returns>
    bool Add(const Key& key, const Value& value) {
        return this->Add(std::pair(key, value));
    }
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="key">キー</param>
    /// <returns>成功</returns>
    bool Remove(const std::string& key) {
        if (!this->Exist(key)) {
            return false;
        } // if
        _elements.erase(key);
        return true;
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="key">キー</param>
    /// <returns>保持していればtrueを返す</returns>
    bool Exist(const Key& key) {
        return _elements.count(key) != 0;
    }
    /// <summary>
    /// 取得
    /// </summary>
    /// <param name="key">キー</param>
    /// <returns></returns>
    Value Find(const Key& key) {
        auto it = _elements.find(key);
        if (it != _elements.end()) {
            return it->second;
        } // if
        if constexpr (std::is_pointer<Value>::value) {
            return nullptr;
        } // if
        return Value();
    }
    /// <summary>
    /// 初期化
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Initialize(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Value>::type;
        using RemovedPtr = typename std::remove_pointer<Value>::type;
        using T = typename std::conditional<ty::is_shared<Value>::value, RemovedShared,
            std::conditional<std::is_pointer<Value>::value, RemovedPtr, Value>::type>::type;

        if constexpr (ty::has_func_initialize<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Value>::value || ty::is_shared<Value>::value) {
                for (auto& elem : _elements) {
                    elem.second->Initialize(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.second.Initialize(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 入力
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Input(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Value>::type;
        using RemovedPtr = typename std::remove_pointer<Value>::type;
        using T = typename std::conditional<ty::is_shared<Value>::value, RemovedShared,
            std::conditional<std::is_pointer<Value>::value, RemovedPtr, Value>::type>::type;

        if constexpr (ty::has_func_input<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Value>::value || ty::is_shared<Value>::value) {
                for (auto& elem : _elements) {
                    elem.second->Input(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.second.Input(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 更新
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Update(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Value>::type;
        using RemovedPtr = typename std::remove_pointer<Value>::type;
        using T = typename std::conditional<ty::is_shared<Value>::value, RemovedShared,
            std::conditional<std::is_pointer<Value>::value, RemovedPtr, Value>::type>::type;

        if constexpr (ty::has_func_update<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Value>::value || ty::is_shared<Value>::value) {
                for (auto& elem : _elements) {
                    elem.second->Update(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.second.Update(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 描画
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Render(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Value>::type;
        using RemovedPtr = typename std::remove_pointer<Value>::type;
        using T = typename std::conditional<ty::is_shared<Value>::value, RemovedShared,
            std::conditional<std::is_pointer<Value>::value, RemovedPtr, Value>::type>::type;

        if constexpr (ty::has_func_render<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Value>::value || ty::is_shared<Value>::value) {
                for (auto& elem : _elements) {
                    elem.second->Render(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.second.Render(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <typeparam name="...Args">引数の型</typeparam>
    /// <param name="...args">引数</param>
    /// <returns>成功</returns>
    template<class...Args>
    auto Release(Args&&...args) {
        using RemovedShared = typename ty::remove_shared<Value>::type;
        using RemovedPtr = typename std::remove_pointer<Value>::type;
        using T = typename std::conditional<ty::is_shared<Value>::value, RemovedShared,
            std::conditional<std::is_pointer<Value>::value, RemovedPtr, Value>::type>::type;

        if constexpr (ty::has_func_release<T, Args...>::value) {
            // pointer
            if constexpr (std::is_pointer<Value>::value || ty::is_shared<Value>::value) {
                for (auto& elem : _elements) {
                    elem.second->Release(args...);
                } // for
                return true;
            } // if
            // value
            else {
                for (auto& elem : _elements) {
                    elem.second.Release(args...);
                } // for
                return true;
            } // else
        } // if
        return false;
    }
};
}
#endif // !MY_ABSTRACT_CONTAINER_H