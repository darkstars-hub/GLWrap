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
/// �A�v���P�[�V����
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
    //! �������t���O
    bool _initialized;
    //! �I���t���O
    bool _end_flag;
    //! �\�����
    my::Application::ApplicationInfo _info;
    //! �E�C���h�E
    std::shared_ptr<my::Window> _window;
    //! �O���t�B�N�X
    my::Graphics _graphics;
    //! ����
    my::InputManager _input;
    //! ���v
    my::Clock _clock;
    //! �Q�[��
    my::GameApplication _game;
    //! ���\�[�X
    my::Application::ResourceMgr _resource;
private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Application();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Application();
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="other">�R�s�[��</param>
    my::Application(const my::Application& other) = delete;
    /// <summary>
    /// �R�s�[������Z�q
    /// </summary>
    /// <param name="other">�R�s�[��</param>
    /// <returns></returns>
    my::Application& operator=(const my::Application& other) = delete;
    /// <summary>
    /// ���[�u�R���X�g���N�^
    /// </summary>
    /// <param name="rhs">�E��</param>
    my::Application(my::Application&& rhs) = delete;
    /// <summary>
    /// ���[�u������Z�q
    /// </summary>
    /// <param name="rhs">�E��</param>
    /// <returns></returns>
    my::Application& operator= (my::Application&& rhs) = delete;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns>����������true��Ԃ�</returns>
    bool Initialize(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="">����������true��Ԃ�</param>
    bool Input(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns>����������true��Ԃ�</returns>
    bool Update(void);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����������true��Ԃ�</returns>
    bool Render(void);
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����������true��Ԃ�</returns>
    bool Release(void);
public:
    /// <summary>
    /// �V���O���g��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static my::Application& GetInstance(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�\�����</returns>
    my::Application::ApplicationInfo GetInfo(void);
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    int Run(void);
};
}
#endif // !MY_APPLICATION_H