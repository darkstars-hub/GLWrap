#ifndef MY_INPUT_MANAGER_H
#define MY_INPUT_MANAGER_H


#include <memory>

#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Gamepad.h"



namespace my {
class InputManager{
private:
    //! �L�[�{�[�h
    std::shared_ptr<my::Keyboard> _keyboard;
    //! �}�E�X
    std::shared_ptr<my::Mouse> _mouse;
    //! �Q�[���p�b�h
    std::shared_ptr<my::Gamepad> _gamepad;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    InputManager();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�L�[�{�[�h</returns>
    std::weak_ptr<my::Keyboard> GetKeyboard(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�}�E�X</returns>
    std::weak_ptr<my::Mouse> GetMouse(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�Q�[���p�b�h</returns>
    std::weak_ptr<my::Gamepad> GetGamepad(void) const;
    /// <summary>
    /// �Z�b�g�A�b�v
    /// </summary>
    /// <param name="window"></param>
    void Setup(const std::shared_ptr<my::Window> window);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void Update(void);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !MY_INPUT_MANAGER_H