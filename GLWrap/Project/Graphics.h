#ifndef MY_GRAPHICS_H
#define MY_GRAPHICS_H


#include "Header.h"


namespace my {
class Graphics {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Graphics();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Graphics();
    /// <summary>
    /// �Z�b�g�A�b�v
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Setup(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns>����������true��Ԃ�</returns>
    bool Initialize(void);

    bool RenderStart(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns>����������true��Ԃ�</returns>
    bool Release (void);

};
}
#endif // !MY_GRAPHICS_H