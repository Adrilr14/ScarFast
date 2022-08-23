#include "input.hpp"
#include "../../facade/Controller.hpp"
#include "../../facade/ControllerMan.hpp"

Keyboard_t::~Keyboard_t() {

}

void Keyboard_t::restart_keyboard() {
    key_A = false;
    key_D = false;
    key_S = false;
    key_W = false;
    key_Right = false;
    key_Left = false;
    key_Down = false;
    key_Up = false;

    key_Enter = false;
    key_Space = false;

    key_shift_left = false;
    key_shift_right = false;
}