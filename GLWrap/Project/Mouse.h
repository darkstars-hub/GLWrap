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
    //! マウスホイール
    static glm::vec2 _mouse_scroll;
    //! ウインドウ
    std::weak_ptr<my::Window> _window;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Mouse();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Mouse();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetWindow(const std::shared_ptr<my::Window>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="position">位置</param>
    void SetCursorPosition(glm::vec2 position);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>マウスホイール</returns>
    glm::vec2 GetMouseScroll(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>位置</returns>
    glm::uvec2 GetMousePosition(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Refresh(void);
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
#endif // !MY_MOUSE_H