#ifndef MY_COLLISION_H
#define MY_COLLISION_H


#include "Circle.h"
#include "Rectangle.h"


namespace my {
class Collision {
public:
    Collision() {
    }
    ~Collision() {
    }
    bool CollisionCircle(const my::Circle& a, const my::Circle& b) {
        return
            std::powf(a.position.x - b.position.x, 2.0f) +
            std::powf(a.position.y - b.position.y, 2.0f) <=
            std::powf(a.radius + b.radius, 2.0f);
    }
    bool CollisionRectangle(const my::Rectangle& a, const my::Rectangle& b) {
        return
            (a.left < b.right) &&
            (b.left < a.right) &&
            (a.top < b.bottom) &&
            (b.top < a.bottom);
    }
    bool CollisionCircleRectangle(const my::Circle& circle, const my::Rectangle& rectangle) {
        float d;
        if (rectangle.left <= circle.position.x && circle.position.x <= rectangle.right &&
            rectangle.top <= circle.position.y && circle.position.y <= rectangle.bottom) {
            return true;
        } // if

        if (std::abs(circle.position.x - rectangle.left) <= circle.radius) {
            d = std::sqrtf(circle.radius * circle.radius -
                           ((circle.position.x - rectangle.left) * (circle.position.x - rectangle.left)));
            if ((rectangle.top <= circle.position.y + d && circle.y + d <= rectangle.bottom) || (rectangle.top <= circle.y - d && circle.y - d <= rectangle.bottom)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.position.x - rectangle.right) <= circle.radius) {
            d = std::sqrtf(circle.radius * circle.radius -
                           ((circle.position.x - rectangle.right) * (circle.position.x - rectangle.right)));
            if ((rectangle.top <= circle.position.y + d && circle.position.y + d <= rectangle.bottom) || (rectangle.top <= circle.position.y - d && circle.position.y - d <= rectangle.bottom)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.position.y - rectangle.top) <= circle.radius) {
            d = std::sqrtf(circle.radius * circle.radius -
                           ((circle.position.y - rectangle.top) * (circle.position.y - rectangle.top)));
            if ((rectangle.left <= circle.position.x + d && circle.position.x + d <= rectangle.right) || (rectangle.left <= circle.position.x - d && circle.position.x - d <= rectangle.right)) {
                return true;
            } // if
        } // if
        if (std::abs(circle.position.y - rectangle.bottom) <= circle.radius) {
            d = std::sqrtf(circle.radius * circle.radius -
                           ((circle.position.y - rectangle.bottom) * (circle.position.y - rectangle.bottom)));
            if ((rectangle.left <= circle.position.x + d && circle.position.x + d <= rectangle.right) || (rectangle.left <= circle.position.x - d && circle.position.x - d <= rectangle.right)) {
                return true;
            } // if
        } // if
        return false;
    }
};
}
#endif // !MY_COLLISION_H