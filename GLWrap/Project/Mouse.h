#ifndef MY_MOUSE_H
#define MY_MOUSE_H


#include <memory>

#include "Window.h"


namespace my {
enum class MouseState {
    None,
    Press,
    Hold,
    Release
};
enum class MouseButton {
    Left,
    Right,
};
class Mouse {
private:
    //! �}�E�X�z�C�[��
    static glm::vec2 _mouse_scroll;
    //! �E�C���h�E
    std::weak_ptr<my::Window> _window;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Mouse();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Mouse();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetWindow(const std::shared_ptr<my::Window>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="position">�ʒu</param>
    void SetCursorPosition(glm::vec2 position);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�}�E�X�z�C�[��</returns>
    glm::vec2 GetMouseScroll(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�ʒu</returns>
    glm::uvec2 GetMousePosition(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Refresh(void);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !MY_MOUSE_H