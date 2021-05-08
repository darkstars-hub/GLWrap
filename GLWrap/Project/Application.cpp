#include "Application.h"

#include "Helper.h"


my::Application::Application() :
    _initialized(false),
    _end_flag(false),
    _window(std::make_shared<my::Window>()),
    _graphics(),
    _input(),
    _clock(),
    _game(),
    _resource(),
    _info(_window, &_input, &_clock, &_resource) {
    ut::IOSetting();
}
my::Application::~Application() {
}

bool my::Application::Initialize(void) {
    _initialized = true;
    // セットアップ
    if (!_graphics.Setup()) {
        return false;
    } // if
    // ウインドウ
    if (!_window->Create()) {
        return false;
    } // if
    // グラフィクス
    if (!_graphics.Initialize()) {
        return false;
    } // if
    // 入力
    _input.Setup(_window);
    // ゲームリソース    
    _resource.Load("../Resource/path/resource.txt");
    // ゲーム
    if (!_game.Initialize()) {
        return false;
    } // if
    return _initialized;
}

bool my::Application::Input(void) {
    _input.Update();
    if (::g_pKeyboard->IsPress(my::KeyCode::Escape) || ::g_pGamepad->IsPress(my::GamepadButton::Back)) {
        _end_flag = true;
    } // if
    // ゲーム
    _game.Input();
    _input.Reset();
    return true;
}

bool my::Application::Update(void) {


    // ゲーム
    _game.Update();
    return true;
}
bool my::Application::Render(void) {
    _graphics.RenderStart();
    // ゲーム
    _game.Render();

    return true;
}

bool my::Application::Release(void) {
    // ゲーム
    _game.Release();
    // window
    _window->Destroy();
    _graphics.Release();
    _initialized = false;
    return true;
}

my::Application& my::Application::GetInstance(void) {
    static my::Application instance;
    return instance;
}

my::Application::ApplicationInfo my::Application::GetInfo(void) {
    return this->_info;
}

int my::Application::Run(void) {
    // 初期化
    if (!this->Initialize()) {
        return -1;
    } // if
    assert(_initialized);
    // メインループ
    //while (true) {
    while (!_window->ShouldClose()) {
        if (_end_flag) { break; } // if
        // 入力
        this->Input();

        // 時間更新 FPS計算 
        _clock.Tick();
        if (!_clock.IsFull()) {
            _clock.Wait(); continue;
        } // if
        _clock.Update();

        // ゲーム更新　描画
        if (!this->Update()) {
            return -1;
        } // if
        if (!this->Render()) {
            return -1;
        } // if

        // 次のフレームへ
        _window->Present();
    } // while


    //  解放
    this->Release();
    return 0;
}