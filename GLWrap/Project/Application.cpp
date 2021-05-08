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
    // �Z�b�g�A�b�v
    if (!_graphics.Setup()) {
        return false;
    } // if
    // �E�C���h�E
    if (!_window->Create()) {
        return false;
    } // if
    // �O���t�B�N�X
    if (!_graphics.Initialize()) {
        return false;
    } // if
    // ����
    _input.Setup(_window);
    // �Q�[�����\�[�X    
    _resource.Load("../Resource/path/resource.txt");
    // �Q�[��
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
    // �Q�[��
    _game.Input();
    _input.Reset();
    return true;
}

bool my::Application::Update(void) {


    // �Q�[��
    _game.Update();
    return true;
}
bool my::Application::Render(void) {
    _graphics.RenderStart();
    // �Q�[��
    _game.Render();

    return true;
}

bool my::Application::Release(void) {
    // �Q�[��
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
    // ������
    if (!this->Initialize()) {
        return -1;
    } // if
    assert(_initialized);
    // ���C�����[�v
    //while (true) {
    while (!_window->ShouldClose()) {
        if (_end_flag) { break; } // if
        // ����
        this->Input();

        // ���ԍX�V FPS�v�Z 
        _clock.Tick();
        if (!_clock.IsFull()) {
            _clock.Wait(); continue;
        } // if
        _clock.Update();

        // �Q�[���X�V�@�`��
        if (!this->Update()) {
            return -1;
        } // if
        if (!this->Render()) {
            return -1;
        } // if

        // ���̃t���[����
        _window->Present();
    } // while


    //  ���
    this->Release();
    return 0;
}