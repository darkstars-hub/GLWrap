#ifndef MY_GAME_PAD_H
#define MY_GAME_PAD_H


#include <array>

#include "Header.h"


namespace my {
enum class GamepadState {
    None,
    Press,
    Hold,
    Release
};
enum class GamepadButton {
    A,
    B,
    X,
    Y,
    DPadUp,
    DPadDown,
    DPadLeft,
    DPadRight,
    LeftShoulder,
    RightShoulder,
    LeftThumb,
    RightThumb,
    Start,
    Back,
    MaxCount,
};
class Gamepad {
private:
    //! ���͏��
    static std::array<my::GamepadState, static_cast<int>(my::GamepadButton::MaxCount)>_button_state;
    //! �{�^�����
    static std::array<int, static_cast<int>(my::GamepadButton::MaxCount)> _button_info;
    //! ��ԕێ�
    XINPUT_STATE _state;
//    GLFWgamepadstate _state;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Gamepad();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Gamepad();
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
    bool IsPress(const my::GamepadButton button) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="code">�L�[</param>
    /// <returns>�����������Ă���Ȃ�true��Ԃ�</returns>
    bool IsHold(const my::GamepadButton button) const;
        /// <summary>
    /// ����
    /// </summary>
    /// <param name="code">�L�[</param>
    /// <returns>�����ꂽ�Ȃ�true��Ԃ�</returns>
    bool IsRelease(const my::GamepadButton button) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns>�g���K�[���|����Ă���Ȃ�true��Ԃ�</returns>
    bool IsActiveLeftTrigger(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns>�g���K�[���|����Ă���Ȃ�true��Ԃ�</returns>
    bool IsActiveRightTrigger(void) const;
    /// <summary>
    /// �X�e�B�b�N�l
    /// </summary>
    /// <param name=""></param>
    /// <returns>���X�e�B�b�NX</returns>
    float GetLeftStickHorizontal(void) const;
    /// <summary>
    /// �X�e�B�b�N�l
    /// </summary>
    /// <param name=""></param>
    /// <returns>���X�e�B�b�NY</returns>
    float GetLeftStickVertical(void) const;
    /// <summary>
    /// �X�e�B�b�N�l
    /// </summary>
    /// <param name=""></param>
    /// <returns>�E�X�e�B�b�NX</returns>
    float GetRightStickHorizontal(void) const;
    /// <summary>
    /// �X�e�B�b�N�l
    /// </summary>
    /// <param name=""></param>
    /// <returns>�E�X�e�B�b�NY</returns>
    float GetRightStickVertical(void) const;
};
}
#endif // !MY_GAME_PAD_H