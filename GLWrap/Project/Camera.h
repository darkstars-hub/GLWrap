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
    //! 位置
    glm::vec3 _position; 
    //! 対象
    glm::vec3 _target; 
    //! 向き
    glm::vec3 _up;
    //! ビュー
    glm::mat4 _view_matrix;
    //! 射影
    glm::mat4 _projection_matrix;
    //! ビュー射影
    glm::mat4 _view_projection;

    void LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
    void UpdateOrtho(void);
    void UpdatePerspective(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Camera();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Camera();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(glm::vec3 pos);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetTarget(glm::vec3 pos);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    glm::vec3 GetPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    glm::vec3 GetCameraRight(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    glm::vec3 GetCameraUp(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>ビュー</returns>
    glm::mat4 GetViewMatrix(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>プロジェクション</returns>
    glm::mat4 GetProjectionMatrix(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns>ビュープロジェクション</returns>
    glm::mat4 GetViewProjectionMatrix(void) const;
    void DebugMoveByMouse(void);
    void DebugMoveTurn(glm::vec3 object_position, float radius, float height);
    void DebugMove(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void Update(void);
};
}
#endif // !MY_CAMERA_H