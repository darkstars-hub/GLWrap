#include "Clock.h"


float my::Clock::_previous_time = 0.0f;
float my::Clock::_delta_time = 0.0f;


void my::Clock::CalculateFPS(void) {
    auto front = _delta_times.front();
    _delta_times.pop_front();
    _delta_times_sum -= front;

    _delta_times.push_back(_delta_time);
    _delta_times_sum += _delta_time;

    auto average = _delta_times_sum / _sample_count;
    _now_fps = 1.0f / average;
}

my::Clock::Clock() :
    _ideal_fps(60.0f),
    _now_fps(0.0f),
    _sample_count(60),
    _delta_times_sum(0.0f),
    _delta_times() {
    ::glfwSetTime(0.0);
    _delta_times.resize(_sample_count, 1.0f / _ideal_fps);
    for (const auto& delta : _delta_times) {
        _delta_times_sum += delta;
    } // for
}

my::Clock::~Clock() {
}

float my::Clock::GetDeltaTime(void) const {
    return this->_delta_time;
}

float my::Clock::GetIdealFPS(void) const noexcept {
    return _ideal_fps;
}

float my::Clock::GetFPS(void) const noexcept {
    return _now_fps;
}

bool my::Clock::IsFull(void) {
    return  1.0f / _ideal_fps <= _delta_time;
}

void my::Clock::Wait(void) {
    _delta_time += (1.0f / _ideal_fps) - _delta_time;
}

void my::Clock::Tick(void) {
    auto current_time = static_cast<float>(::glfwGetTime());
    _delta_time = current_time - _previous_time;
    this->CalculateFPS();
}

void my::Clock::Update(void) {
    _previous_time = static_cast<float>(::glfwGetTime());
}