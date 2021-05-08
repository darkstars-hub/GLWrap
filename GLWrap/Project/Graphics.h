#ifndef MY_GRAPHICS_H
#define MY_GRAPHICS_H


#include "Header.h"


namespace my {
class Graphics {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Graphics();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Graphics();
    /// <summary>
    /// セットアップ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Setup(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Initialize(void);

    bool RenderStart(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Release (void);

};
}
#endif // !MY_GRAPHICS_H