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
    //! キーボード
    std::shared_ptr<my::Keyboard> _keyboard;
    //! マウス
    std::shared_ptr<my::Mouse> _mouse;
    //! ゲームパッド
    std::shared_ptr<my::Gamepad> _gamepad;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    InputManager();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>キーボード</returns>
    std::weak_ptr<my::Keyboard> GetKeyboard(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>マウス</returns>
    std::weak_ptr<my::Mouse> GetMouse(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>ゲームパッド</returns>
    std::weak_ptr<my::Gamepad> GetGamepad(void) const;
    /// <summary>
    /// セットアップ
    /// </summary>
    /// <param name="window"></param>
    void Setup(const std::shared_ptr<my::Window> window);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void Update(void);
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !MY_INPUT_MANAGER_H