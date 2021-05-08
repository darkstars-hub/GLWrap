#ifndef MY_SPRITE_ANIMATION_H
#define MY_SPRITE_ANIMATION_H


#include <string>
#include <vector>

#include "glm/glm.hpp"

#include "Rectangle.h"


namespace my {
class SpriteAnimation {
private:
    //! ���O
    std::string _name;
    //! �C���f�b�N�X
    uint32_t _index;
    //! �t���[���J�E���g
    std::size_t _frame_count;
    //! ���[�g
    uint32_t _rate;
    //! �`���`�z��
    std::vector<my::Rectangle> _rectangles;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SpriteAnimation();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SpriteAnimation();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="index"></param>
    void SetCurrentIndex(uint32_t index);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="rate"></param>
    void SetRate(uint32_t rate);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    uint32_t GetCurrentIndex(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    uint32_t GetRate(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Rectangle GetRectangle(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns>�I��</returns>
    bool IsEnd(void) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="rectangle"></param>
    void AddRectangle(my::Rectangle rectangle);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void ResetRectangles(void);
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !MY_SPRITE_ANIMATION_H