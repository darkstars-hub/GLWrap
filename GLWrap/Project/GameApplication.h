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
    /// �R���X�g���N�^
    /// </summary>
    GameApplication();    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~GameApplication();
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
};
}
#endif // !MY_GAME_Application_H