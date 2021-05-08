#ifndef MY_CIRCLE_H
#define MY_CIRCLE_H


#include "Header.h"


namespace my {
class Circle {
public:
    union {
        struct {
            float x;
            float y;
        };
        struct {
            glm::vec2 position;
        };
    };
    float radius;

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Circle() : radius(0.0f), position() {}
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="x">x</param>
    /// <param name="y">y</param>
    /// <param name="r">半径</param>
    Circle(float x, float y, float r) :position(x, y), radius(r) {}
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="pos">位置</param>
    /// <param name="r">半径</param>
    Circle(glm::vec2 pos, float r) :Circle(pos.x, pos.y, r) {}

    Circle operator+(glm::vec2 translate) {
        return Circle(
            this->radius,
            this->position.x + translate.x,
            this->position.x + translate.y);
    }
    Circle& operator+=(glm::vec2 translate) {
        this->position += translate;
        return *this;
    }
    bool CollisionCircle(const Circle& circle) {
        return
            std::powf(this->position.x - circle.position.x, 2.0f) +
            std::powf(this->position.y - circle.position.y, 2.0f) <=
            std::powf(this->radius + circle.radius, 2.0f);
    }
    void Translate(float x, float y) {
        this->position.x += x;
        this->position.y += y;
    }
    void Translate(glm::vec2 vector) {
        this->Translate(vector.x, vector.y);
    }
};
}
#endif // !MY_CIRCLE_H