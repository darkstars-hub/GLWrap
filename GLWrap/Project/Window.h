#ifndef MY_WINDOW_H
#define MY_WINDOW_H


#include "Header.h"


namespace my {
class Window {
private:
    //! �n���h��
    GLFWwindow* _handle;
    //! �T�C�Y
    glm::uvec2 _size;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Window();
    /// <summary>
    /// �f���X�g���N�^
    /// </summary>
    ~Window();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="">�n���h��</param>
    ::GLFWwindow* GetHandle(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�T�C�Y</returns>
    glm::uvec2 GetSize(void) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns>����������true��Ԃ�</returns>
    bool Create(void);
    /// <summary>
    /// �j��
    /// </summary>
    /// <param name=""></param>
    void Destroy(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns>���Ă����true��Ԃ�</returns>
    bool ShouldClose(void) const;
    /// <summary>
    /// �o�b�t�@����ւ��@
    /// </summary>
    /// <param name=""></param>
    void Present(void) const;
};
}
#endif // !MY_WINDOW_H