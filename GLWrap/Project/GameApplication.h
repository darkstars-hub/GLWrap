#ifndef MY_GAME_APPLICATION_H
#define MY_GAME_APPLICATION_H


#include "Camera.h"
#include "GeometryRenderer.h"


namespace my {
class GameApplication {
private:
    my::Camera _camera;

    my::GeometryRenderer _geometry_renderer;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameApplication();    
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameApplication();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Initialize(void);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name="">成功したらtrueを返す</param>
    bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Update(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Render(void);
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功したらtrueを返す</returns>
    bool Release(void);
};
}
#endif // !MY_GAME_Application_H