#include "SpriteAnimation.h"

#include "rapidjson/document.h"

#include "Helper.h"


my::SpriteAnimation::SpriteAnimation() :
    _index(0),
    _frame_count(0),
    _rate(0),
    _rectangles() {
}

my::SpriteAnimation::~SpriteAnimation() {
}

void my::SpriteAnimation::SetCurrentIndex(uint32_t index) {
    this->_index = index;
}

void my::SpriteAnimation::SetRate(uint32_t rate) {
    this->_rate = rate;
}

uint32_t my::SpriteAnimation::GetCurrentIndex(void) const {
    return this->_index;
}

uint32_t my::SpriteAnimation::GetRate(void) const {
    return this->_rate;
}

my::Rectangle my::SpriteAnimation::GetRectangle(void) const {
    auto it = _rectangles.begin();
    return *(it + _index);
}

bool my::SpriteAnimation::IsEnd(void) const {
    return _index == 0 && _frame_count == 0;
}

void my::SpriteAnimation::AddRectangle(my::Rectangle rectangle) {
    _rectangles.push_back(rectangle);
}

void my::SpriteAnimation::ResetRectangles(void) {
    _rectangles.clear();
}

bool my::SpriteAnimation::Load(const char* path) {
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return false;
    } // if
    if (!document.HasMember("animation")) {
        return false;
    } // if
    // 
    auto& animation = document["animation"];

    if (animation.HasMember("name")) {
        assert(animation["name"].IsString());
        _name = animation["name"].GetString();
    } // if
    if (animation.HasMember("rate")) {
        assert(animation["rate"].IsInt());
        _rate = animation["rate"].GetInt();
    } // if
    if (animation.HasMember("rectangles")) {
        auto& rectangles = animation["rectangles"];
        size_t n = rectangles.Size();
        _rectangles.resize(n);
        for (size_t i = 0; i < n; i++) {
            assert(rectangles[i].HasMember("left"));
            assert(rectangles[i].HasMember("top"));
            assert(rectangles[i].HasMember("right"));
            assert(rectangles[i].HasMember("bottom"));

            _rectangles.at(i).left = static_cast<float>( rectangles[i]["left"].GetInt());
            _rectangles.at(i).top = static_cast<float>(rectangles[i]["top"].GetInt());
            _rectangles.at(i).right = static_cast<float>(rectangles[i]["right"].GetInt());
            _rectangles.at(i).bottom = static_cast<float>(rectangles[i]["bottom"].GetInt());
        } // for
    } // if
    return true;
}

bool my::SpriteAnimation::Update(void) {
    _frame_count++;
    if (_rate < _frame_count) {
        _index++;
        _frame_count = 0;
    } // if
    if (_rectangles.size() <= _index) {
        _index = 0;
    } // if
    return true;
}