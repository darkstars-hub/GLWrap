#ifndef MY_CLOCK_H
#define MY_CLOCK_H


#include <deque>

#include "Header.h"


namespace my {
class Clock {
private:
    //! ���݂̃f���^�^�C��
    static float _delta_time;
    //! �O�̃f���^�^�C��
    static float _previous_time;
    //! ���z�I��FPS
    float _ideal_fps;
    //! ���݂�FPS
    float _now_fps;
    //! �W�{��
    const int _sample_count;
    //! �f���^�^�C���̍��v�l
    float _delta_times_sum;
    //! �W�{
    std::deque<float> _delta_times;
    /// <summary>
    /// FPS�Z�o
    /// </summary>
    /// <param name=""></param>
    void CalculateFPS(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Clock();
    /// <summary>
    /// �f���X�g���N�^
    /// </summary>
    ~Clock();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>�f���^�^�C��</returns>
    float GetDeltaTime(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>���z�I��FPS</returns>
    float GetIdealFPS(void) const noexcept;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns>���݂�FPS</returns>
    float GetFPS(void) const noexcept;
    /// <summary>
    /// �P�ʎ��Ԃɓ��B���������肷��
    /// </summary>
    /// <param name=""></param>
    /// <returns>���Ă���Ȃ�true��Ԃ�</returns>
    bool IsFull(void);
    /// <summary>
    /// �P�ʎ��ԂɂȂ�܂ő҂�
    /// </summary>
    /// <param name=""></param>
    void Wait(void);
    /// <summary>
    /// ���Ԃ�i�߂�
    /// </summary>
    /// <param name=""></param>
    void Tick(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void Update(void);
};
}
#endif // !MY_CLOCK_H