#ifndef MY_CAMERA_H
#define MY_CAMERA_H


#include "glm/glm.hpp"


namespace my {
class Camera {
private:
    float _fovy; 
    float _aspect; 
    float _near; 
    float _far;
    //! �ʒu
    glm::vec3 _position; 
    //! �Ώ�
    glm::vec3 _target; 
    //! ����
    glm::vec3 _up;
    //! �r���[
    glm::mat4 _view_matrix;
    //! �ˉe
    glm::mat4 _projection_matrix;
    //! �r���[�ˉe
    glm::mat4 _view_projection;

    void LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
    void UpdateOrtho(void);
    void UpdatePerspective(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Camera();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Camera();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(glm::vec3 pos);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="pos"></param>
    void SetTarget(glm::vec3 pos);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    glm::vec3 GetPosition(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    glm::vec3 GetCameraRight(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    glm::vec3 GetCameraUp(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�r���[</returns>
    glm::mat4 GetViewMatrix(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�v���W�F�N�V����</returns>
    glm::mat4 GetProjectionMatrix(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�r���[�v���W�F�N�V����</returns>
    glm::mat4 GetViewProjectionMatrix(void) const;
    void DebugMoveByMouse(void);
    void DebugMoveTurn(glm::vec3 object_position, float radius, float height);
    void DebugMove(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void Update(void);
};
}
#endif // !MY_CAMERA_H