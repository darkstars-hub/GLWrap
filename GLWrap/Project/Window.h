#ifndef MY_WINDOW_H
#define MY_WINDOW_H


#include "Header.h"


namespace my {
class Window {
private:
    //! ハンドル
    GLFWwindow* _handle;
    //! サイズ
    glm::uvec2 _size;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Window();
    /// <summary>
    /// デンストラクタ
    /// </summary>
    ~Window();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="">ハンドル</param>
    ::GLFWwindow* GetHandle(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>サイズ</returns>
    glm::uvec2 GetSize(void) const;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Create(void);
    /// <summary>
    /// 破棄
    /// </summary>
    /// <param name=""></param>
    void Destroy(void);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns>閉じていればtrueを返す</returns>
    bool ShouldClose(void) const;
    /// <summary>
    /// バッファ入れ替え　
    /// </summary>
    /// <param name=""></param>
    void Present(void) const;
};
}
#endif // !MY_WINDOW_H