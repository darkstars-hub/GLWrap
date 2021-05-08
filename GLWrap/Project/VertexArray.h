#ifndef MY_VERTEX_ARRAY_H
#define MY_VERTEX_ARRAY_H


#include <type_traits>
#include <vector>

#include "Header.h"
#include "Vertex.h"


struct has_position_impl {
    template <class T>
    static std::true_type check(decltype(T::position)*);
    template <class T>
    static std::false_type check(...);
};
template <class T>
class has_position : public decltype(has_position_impl::check<T>(nullptr)) {};

struct has_color_impl {
    template <class T>
    static std::true_type check(decltype(T::color)*);
    template <class T>
    static std::false_type check(...);
};
template <class T>
class has_color : public decltype(has_color_impl::check<T>(nullptr)) {};


namespace my {
template<class Vertex>
class VertexArray {
private:
    //! ハンドル
    GLuint _vertex_array;
    //! 頂点
    GLuint _vertex_buffer;
    //! 各頂点
    std::vector<Vertex> _vertices;
    //! 各インデックス
    std::vector<uint32_t> _indices;
    //! トポロジー
    GLenum _topology;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    VertexArray();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="vertices">頂点データ</param>
    /// <param name="indices">インデックスデータ</param>
    VertexArray(std::vector<Vertex>& vertices,
                std::vector<uint32_t>& indices);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~VertexArray();
    /// <summary>
    /// ハンドル
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    GLuint GetID(void) const;
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Generate(int vertex_usage = GL_STATIC_DRAW);
    /// <summary>
    /// バインド
    /// </summary>
    /// <param name=""></param>
    void Bind(void);
    /// <summary>
    /// 解除
    /// </summary>
    /// <param name=""></param>
    void UnBind(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <typeparam name="Vertex"></typeparam>
    void Update(const std::vector<Vertex>& vertices);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    bool RenderInstanced(std::size_t count);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Delete(void);
    /// <summary>
    /// トポロジーをLINE_STRIPにする
    /// </summary>
    /// <param name=""></param>
    void ToLineStrip(void);
    /// <summary>
    /// トポロジーをTRIANGLE_STRIPにする
    /// </summary>
    /// <param name=""></param>
    void ToTriangleStrip(void);
    /// <summary>
    /// トポロジーをTRIANGLESにする
    /// </summary>
    /// <param name=""></param>
    void ToTriangles(void);
};
}

template<class Vertex>
inline my::VertexArray<Vertex>::VertexArray() :
    _vertex_array(0),
    _vertex_buffer(0),
    _vertices(),
    _indices(),
    _topology(GL_TRIANGLE_STRIP) {
}

template<class Vertex>
inline my::VertexArray<Vertex>::VertexArray(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) :
    _vertex_array(0),
    _vertex_buffer(0),
    _vertices(vertices),
    _indices(indices),
    _topology(GL_TRIANGLE_STRIP) {
}
template<class Vertex>
inline my::VertexArray<Vertex>::~VertexArray() {
//    _ASSERT_EXPR(!_vertex_array,
  //               L"バーテックスアレイが解放されていません");
}
template<class Vertex>
inline GLuint my::VertexArray<Vertex>::GetID(void) const {
    return this->_vertex_array;
}
template<class Vertex>
inline bool my::VertexArray<Vertex>::Generate(int vertex_usage) {
    // 生成
    ::glGenVertexArrays(1, &_vertex_array);
    ::glBindVertexArray(_vertex_array);
    // 各バッファ作成

    GLuint index_buffer;
    ::glGenBuffers(1, &_vertex_buffer);
    ::glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    ::glBufferData(GL_ARRAY_BUFFER,
                   sizeof(Vertex) * _vertices.size(),
                   _vertices.data(),
                   vertex_usage);
    ::glGenBuffers(1, &index_buffer);
    ::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    ::glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   sizeof(uint32_t) * _indices.size(),
                   _indices.data(),
                   GL_STATIC_DRAW);

    if constexpr (std::is_same<Vertex, my::SimpleVertex>::value) {
        // 頂点属性設定
        int pos = 0; // index
        ::glEnableVertexAttribArray(pos);
        ::glVertexAttribPointer(
            pos,
            sizeof(Vertex::position) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast <GLvoid*>(offsetof(Vertex, Vertex::position)));
    } // if
    else if constexpr (std::is_same<Vertex, my::FontVertex>::value) {
        int pos = 0;
        ::glEnableVertexAttribArray(pos);
        ::glVertexAttribPointer(
            pos,
            sizeof(Vertex::position) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast <GLvoid*>(offsetof(Vertex, Vertex::position)));
        int texcoord = 1;
        ::glEnableVertexAttribArray(texcoord);
        ::glVertexAttribPointer(
            texcoord,
            sizeof(Vertex::texcoord) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast <GLvoid*>(offsetof(Vertex, Vertex::texcoord)));
    } // else if
    else if constexpr (std::is_same<Vertex, my::ColorVertex>::value) {
        // 頂点属性設定
        int pos = 0; // index
        ::glEnableVertexAttribArray(pos);
        ::glVertexAttribPointer(
            pos,
            sizeof(Vertex::position) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast <GLvoid*>(offsetof(Vertex, Vertex::position)));
        int color = 1; // index
        ::glEnableVertexAttribArray(color);
        ::glVertexAttribPointer(
            color,
            sizeof(Vertex::color) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::color)));
    } // else if
    else if constexpr (std::is_same<Vertex, my::NormalVertex>::value) {
        // 頂点属性設定
        int pos = 0; // index
        ::glEnableVertexAttribArray(pos);
        ::glVertexAttribPointer(
            pos,
            sizeof(Vertex::position) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast <GLvoid*>(offsetof(Vertex, Vertex::position)));
        int uv = 1; // index
        ::glEnableVertexAttribArray(uv);
        ::glVertexAttribPointer(
            uv,
            sizeof(Vertex::uv) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::uv)));
        int normal = 2; // index
        ::glEnableVertexAttribArray(normal);
        ::glVertexAttribPointer(
            normal,
            sizeof(Vertex::normal) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::normal)));
    } // if
    else if constexpr (std::is_same<Vertex, my::SkinVertex>::value) {
        // 頂点属性設定
        int pos = 0; // index
        ::glEnableVertexAttribArray(pos);
        ::glVertexAttribPointer(
            pos,
            sizeof(Vertex::position) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast <GLvoid*>(offsetof(Vertex, Vertex::position)));
        int normal = 1; // index
        ::glEnableVertexAttribArray(normal);
        ::glVertexAttribPointer(
            normal,
            sizeof(Vertex::normal) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::normal)));
        int texcoord0 = 2; // index
        ::glEnableVertexAttribArray(texcoord0);
        ::glVertexAttribPointer(
            texcoord0,
            sizeof(Vertex::texcoord0) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::texcoord0)));
        int texcoord1 = 3; // index
        ::glEnableVertexAttribArray(texcoord1);
        ::glVertexAttribPointer(
            texcoord1,
            sizeof(Vertex::texcoord1) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::texcoord1)));
        int texcoord2 = 4; // index
        ::glEnableVertexAttribArray(texcoord2);
        ::glVertexAttribPointer(
            texcoord2,
            sizeof(Vertex::texcoord2) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::texcoord2)));
        int texcoord3 = 5; // index
        ::glEnableVertexAttribArray(texcoord3);
        ::glVertexAttribPointer(
            texcoord3,
            sizeof(Vertex::texcoord3) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::texcoord3)));
        int texcoord4 = 6; // index
        ::glEnableVertexAttribArray(texcoord4);
        ::glVertexAttribPointer(
            texcoord4,
            sizeof(Vertex::texcoord4) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::texcoord4)));
        int color = 7; // index
        ::glEnableVertexAttribArray(color);
        ::glVertexAttribPointer(
            color,
            sizeof(Vertex::color) / sizeof(float),
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::color)));
        int joints = 8;
        glEnableVertexAttribArray(joints);
        glVertexAttribIPointer(
            joints,
            sizeof(Vertex::joints) / sizeof(uint16_t),
            GL_UNSIGNED_SHORT,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::joints)));
        int weights = 9; // index
        ::glEnableVertexAttribArray(weights);
        ::glVertexAttribPointer(
            weights,
            sizeof(Vertex::weights) / sizeof(float),
            GL_FLOAT,
            GL_TRUE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::weights)));
        int tangent = 10; // index
        ::glEnableVertexAttribArray(tangent);
        ::glVertexAttribPointer(
            tangent,
            sizeof(Vertex::tangent) / sizeof(float),
            GL_FLOAT,
            GL_TRUE,
            sizeof(Vertex),
            reinterpret_cast<GLvoid*>(offsetof(Vertex, Vertex::tangent)));
    } // else if
    return true;
}
template<class Vertex>
inline void my::VertexArray<Vertex>::Bind(void) {
    ::glBindVertexArray(_vertex_array);
}
template<class Vertex>
inline void my::VertexArray<Vertex>::UnBind(void) {
    ::glBindVertexArray(0);
}
template<class Vertex>
inline void my::VertexArray<Vertex>::Update(const std::vector<Vertex>& vertices) {
    ::glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
    ::glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), vertices.data());
}
template<class Vertex>
inline bool my::VertexArray<Vertex>::Render(void) {
    ::glDrawElements(_topology,
                     _indices.size(),
                     GL_UNSIGNED_INT,
                     nullptr);
    return true;
}
template<class Vertex>
inline bool my::VertexArray<Vertex>::RenderInstanced(std::size_t count) {
    ::glDrawElementsInstanced(_topology,
                              _indices.size(),
                              GL_UNSIGNED_INT,
                              nullptr,
                              count);
    return true;
}
template<class Vertex>
inline bool my::VertexArray<Vertex>::Delete(void) {
    ::glDeleteVertexArrays(1, &_vertex_array);
    _vertex_array = NULL;
    return true;
}
template<class Vertex>
inline void my::VertexArray<Vertex>::ToLineStrip(void) {
    _topology = GL_LINE_STRIP;
}
template<class Vertex>
inline void my::VertexArray<Vertex>::ToTriangleStrip(void) {
    _topology = GL_TRIANGLE_STRIP;
}
template<class Vertex>
inline void my::VertexArray<Vertex>::ToTriangles(void) {
    _topology = GL_TRIANGLES;
}
#endif // !MY_VERTEX_ARRAY_H