#ifndef MY_RECTANGLE_H
#define MY_RECTANGLE_H


#include "Header.h"


namespace my {
class Rectangle {
public:
    float left, top, right, bottom;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Rectangle() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {
    }
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="l"></param>
    /// <param name="t"></param>
    /// <param name="r"></param>
    /// <param name="b"></param>
    Rectangle(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {
    }
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="lt"></param>
    /// <param name="rb"></param>
    Rectangle(glm::vec2 lt, glm::vec2 rb) : Rectangle(lt.x, lt.y, rb.x, rb.y) {
    }

    Rectangle operator+(glm::vec2 translate) {
        return Rectangle(
            this->left + translate.x,
            this->top + translate.y,
            this->right + translate.x,
            this->bottom + translate.y);
    }
    Rectangle& operator+=(glm::vec2 translate) {
        this->left += translate.x;
        this->top += translate.y;
        this->right += translate.x;
        this->bottom += translate.y;
        return *this;
    }

    bool CollisionRectangle(const Rectangle& rectangle) {
        return
            (this->left < rectangle.right) &&
            (rectangle.left < this->right) &&
            (this->top < rectangle.bottom) &&
            (rectangle.top < this->bottom);
    }
    /*
    bool CollisionCircle(const Circle& circle) {
        float d;
        if (this->left <= circle.x_ && circle.x_ <= this->right &&
            this->top <= circle.y_ && circle.y_ <= this->bottom) {
            return true;
        } // if

        if (std::abs(circle.x_ - this->left) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                           ((circle.x_ - this->left) * (circle.x_ - this->left)));
            if ((this->top <= circle.y_ + d && circle.y + d <= this->bottom) || (this->top <= circle.y - d && circle.y - d <= this->bottom)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.x_ - this->right) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                           ((circle.x_ - this->right) * (circle.x_ - this->right)));
            if ((this->top <= circle.y_ + d && circle.y_ + d <= this->bottom) || (this->top <= circle.y_ - d && circle.y_ - d <= this->bottom)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.y_ - this->top) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                           ((circle.y_ - this->top) * (circle.y_ - this->top)));
            if ((this->left <= circle.x_ + d && circle.x_ + d <= this->right) || (this->left <= circle.x_ - d && circle.x_ - d <= this->right)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.y_ - this->bottom) <= circle.radius_) {
            d = std::sqrtf(circle.radius_ * circle.radius_ -
                           ((circle.y_ - this->bottom) * (circle.y_ - this->bottom)));
            if ((this->left <= circle.x_ + d && circle.x_ + d <= this->right) || (this->left <= circle.x_ - d && circle.x_ - d <= this->right)) {
                return true;
            } // if
        } // if
        return false;
    }
    */

    void Translate(float x, float y) {
        this->left += x;
        this->top += y;
        this->right += x;
        this->bottom += y;
    }
    void Translate(glm::vec2 vector) {
        this->Translate(vector.x, vector.y);
    }
    void SetBound(float left, float top, float right, float bottom) {
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
    }
    float GetWidth(void) const {
        return this->right - this->left;
    }
    float GetHeight(void) const {
        return this->bottom - this->top;
    }
    glm::vec2 GetSize(void) const {
        return glm::vec2(this->GetWidth(), this->GetHeight());
    }
    void Expansion(const float value) {
        this->left -= value;
        this->top -= value;
        this->right += value;
        this->bottom += value;
    }
};
}
#endif // !MY_RECTANGLE_H