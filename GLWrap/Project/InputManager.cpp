#include "InputManager.h"

my::InputManager::InputManager() :
    _keyboard(std::make_shared<my::Keyboard>()),
    _mouse(std::make_shared<my::Mouse>()),
    _gamepad(std::make_shared<my::Gamepad>()) {
}

std::weak_ptr<my::Keyboard> my::InputManager::GetKeyboard(void) const {
    return this->_keyboard;
}

std::weak_ptr<my::Mouse> my::InputManager::GetMouse(void) const {
    return this->_mouse;
}

std::weak_ptr<my::Gamepad> my::InputManager::GetGamepad(void) const {
    return this->_gamepad;
}

void my::InputManager::Setup(const std::shared_ptr<my::Window> window){
    _keyboard->SetWindow(window);
    _mouse->SetWindow(window);
}

void my::InputManager::Update(void) {
    _keyboard->Refresh();
    _mouse->Refresh();
    _gamepad->Refresh();
}

void my::InputManager::Reset(void) {
    _mouse->Reset();
}