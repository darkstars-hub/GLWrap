#ifndef MY_GEOMETRY_RENDERER_H
#define MY_GEOMETRY_RENDERER_H


#include <memory>
#include <string>
#include <unordered_map>

#include "Vertex.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Circle.h"
#include "Rectangle.h"


namespace my {
class GeometryRenderer {
    struct Pair {
        std::weak_ptr<my::Shader> shader;
        my::VertexArray<SimpleVertex> buffer;
    };
private:
    //! �V�F�[�_�ƃo�b�t�@
    std::unordered_map<std::string, Pair> _pair_map;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InitializeFillTriangle(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InitializeFillCircle(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InitializeLineCircle(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InitializeFillRectangle(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GeometryRenderer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GeometryRenderer();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);

    bool RenderFillTriangle(glm::vec3 position, glm::quat rotate, glm::vec3 scale, glm::vec4 color, glm::mat4 view, glm::mat4 proj);
    bool RenderFillCircle(const my::Circle& circle, glm::vec4 color, glm::mat4 view, glm::mat4 proj);
    bool RenderLineCircle(const my::Circle& circle, glm::vec4 color, glm::mat4 view, glm::mat4 proj);
    bool RenderFillRectangle(const my::Rectangle& rectangle, glm::vec4 color, glm::mat4 view, glm::mat4 proj);
};
}
#endif // !MY_GEOMETRY_RENDERER_H