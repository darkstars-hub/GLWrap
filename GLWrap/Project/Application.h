#ifndef MY_APPLICATION_H
#define MY_APPLICATION_H


#include "Header.h"
#include "Window.h"
#include "Graphics.h"
#include "InputManager.h"
#include "Clock.h"
#include "GameApplication.h"
#include "ResourceManager.h"


#define g_pKeyboard my::Application::GetInstance().GetInfo().input->GetKeyboard().lock()
#define g_pGamepad  my::Application::GetInstance().GetInfo().input->GetGamepad().lock()
#define g_pMouse    my::Application::GetInstance().GetInfo().input->GetMouse().lock()
#define g_pClock    my::Application::GetInstance().GetInfo().clock
#define g_pResource my::Application::GetInstance().GetInfo().resource


namespace my {
/// <summary>
/// アプリケーション
/// </summary>
class Application {
    using ResourceMgr = my::ResourceManager<std::shared_ptr< my::Shader>, std::shared_ptr<my::Texture>, std::shared_ptr<my::Model> >;
    struct ApplicationInfo {
        std::shared_ptr<my::Window> window;
        my::InputManager* input;
        my::Clock* clock;
        my::Application::ResourceMgr* resource;
        ApplicationInfo(std::shared_ptr<my::Window> w,
                        my::InputManager* i,
                        my::Clock* c,
                        my::Application::ResourceMgr* r) :
            window(w),
            input(i),
            resource(r),
            clock(c) {
        }
    };
private:
    //! 初期化フラグ
    bool _initialized;
    //! 終了フラグ
    bool _end_flag;
    //! 構成情報
    my::Application::ApplicationInfo _info;
    //! ウインドウ
    std::shared_ptr<my::Window> _window;
    //! グラフィクス
    my::Graphics _graphics;
    //! 入力
    my::InputManager _input;
    //! 時計
    my::Clock _clock;
    //! ゲーム
    my::GameApplication _game;
    //! リソース
    my::Application::ResourceMgr _resource;
private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Application();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Application();
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="other">コピー元</param>
    my::Application(const my::Application& other) = delete;
    /// <summary>
    /// コピー代入演算子
    /// </summary>
    /// <param name="other">コピー元</param>
    /// <returns></returns>
    my::Application& operator=(const my::Application& other) = delete;
    /// <summary>
    /// ムーブコンストラクタ
    /// </summary>
    /// <param name="rhs">右辺</param>
    my::Application(my::Application&& rhs) = delete;
    /// <summary>
    /// ムーブ代入演算子
    /// </summary>
    /// <param name="rhs">右辺</param>
    /// <returns></returns>
    my::Application& operator= (my::Application&& rhs) = delete;
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
public:
    /// <summary>
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static my::Application& GetInstance(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>構成情報</returns>
    my::Application::ApplicationInfo GetInfo(void);
    /// <summary>
    /// 実行
    /// </summary>
    /// <param name=""></param>
    /// <returns>結果</returns>
    int Run(void);
};
}
#endif // !MY_APPLICATION_H