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
    //! 入力状態
    static std::array<my::GamepadState, static_cast<int>(my::GamepadButton::MaxCount)>_button_state;
    //! ボタン情報
    static std::array<int, static_cast<int>(my::GamepadButton::MaxCount)> _button_info;
    //! 状態保持
    XINPUT_STATE _state;
//    GLFWgamepadstate _state;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Gamepad();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Gamepad();
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
    bool IsPress(const my::GamepadButton button) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="code">キー</param>
    /// <returns>押し続けられているならtrueを返す</returns>
    bool IsHold(const my::GamepadButton button) const;
        /// <summary>
    /// 判定
    /// </summary>
    /// <param name="code">キー</param>
    /// <returns>離されたならtrueを返す</returns>
    bool IsRelease(const my::GamepadButton button) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns>トリガーが倒されているならtrueを返す</returns>
    bool IsActiveLeftTrigger(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns>トリガーが倒されているならtrueを返す</returns>
    bool IsActiveRightTrigger(void) const;
    /// <summary>
    /// スティック値
    /// </summary>
    /// <param name=""></param>
    /// <returns>左スティックX</returns>
    float GetLeftStickHorizontal(void) const;
    /// <summary>
    /// スティック値
    /// </summary>
    /// <param name=""></param>
    /// <returns>左スティックY</returns>
    float GetLeftStickVertical(void) const;
    /// <summary>
    /// スティック値
    /// </summary>
    /// <param name=""></param>
    /// <returns>右スティックX</returns>
    float GetRightStickHorizontal(void) const;
    /// <summary>
    /// スティック値
    /// </summary>
    /// <param name=""></param>
    /// <returns>右スティックY</returns>
    float GetRightStickVertical(void) const;
};
}
#endif // !MY_GAME_PAD_H