#ifndef MY_SPRITE_ANIMATION_H
#define MY_SPRITE_ANIMATION_H


#include <string>
#include <vector>

#include "glm/glm.hpp"

#include "Rectangle.h"


namespace my {
class SpriteAnimation {
private:
    //! 名前
    std::string _name;
    //! インデックス
    uint32_t _index;
    //! フレームカウント
    std::size_t _frame_count;
    //! レート
    uint32_t _rate;
    //! 描画矩形配列
    std::vector<my::Rectangle> _rectangles;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SpriteAnimation();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SpriteAnimation();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="index"></param>
    void SetCurrentIndex(uint32_t index);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="rate"></param>
    void SetRate(uint32_t rate);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    uint32_t GetCurrentIndex(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    uint32_t GetRate(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Rectangle GetRectangle(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns>終了</returns>
    bool IsEnd(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="rectangle"></param>
    void AddRectangle(my::Rectangle rectangle);
    /// <summary>
    /// リセット
    /// </summary>
    /// <param name=""></param>
    void ResetRectangles(void);
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    bool Load(const char* path);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !MY_SPRITE_ANIMATION_H