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
    //! 入力状態
    static std::array<my::KeyState, static_cast<int>(my::KeyCode::MaxCount)>_key_status;
    //! キー情報
    static std::array<int, static_cast<int>(my::KeyCode::MaxCount)> _key_codes;
    //! ウインドウ
    std::weak_ptr<my::Window> _window;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Keyboard();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetWindow(const std::shared_ptr<my::Window>& ptr);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    bool Refresh(void);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="code">キー</param>
    /// <returns>押されたならtrueを返す</returns>
    bool IsPress(const my::KeyCode code) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="code">キー</param>
    /// <returns>押し続けられているならtrueを返す</returns>
    bool IsHold(const my::KeyCode code) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="code">キー</param>
    /// <returns>離されたならtrueを返す</returns>
    bool IsRelease(const my::KeyCode code) const;
};
}
#endif // !MY_KEYBOARD_H 