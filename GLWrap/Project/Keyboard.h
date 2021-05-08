#ifndef MY_KEYBOARD_H 
#define MY_KEYBOARD_H 


#include <memory>
#include <array>

#include "Header.h"
#include "Window.h"


namespace my {
enum class KeyState {
    None,
    Press,
    Hold,
    Release
};
enum class KeyCode {
    Space,
    Up,
    Down,
    Right,
    Left,
    Enter,
    Escape,
    MaxCount,
};
class Keyboard {
private:
    //! ���͏��
    static std::array<my::KeyState, static_cast<int>(my::KeyCode::MaxCount)>_key_status;
    //! �L�[���
    static std::array<int, static_cast<int>(my::KeyCode::MaxCount)> _key_codes;
    //! �E�C���h�E
    std::weak_ptr<my::Window> _window;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Keyboard();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetWindow(const std::shared_ptr<my::Window>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    bool Refresh(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="code">�L�[</param>
    /// <returns>�����ꂽ�Ȃ�true��Ԃ�</returns>
    bool IsPress(const my::KeyCode code) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="code">�L�[</param>
    /// <returns>�����������Ă���Ȃ�true��Ԃ�</returns>
    bool IsHold(const my::KeyCode code) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="code">�L�[</param>
    /// <returns>�����ꂽ�Ȃ�true��Ԃ�</returns>
    bool IsRelease(const my::KeyCode code) const;
};
}
#endif // !MY_KEYBOARD_H 