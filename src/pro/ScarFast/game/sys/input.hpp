#pragma once

class Keyboard_t {

public:
    bool key_W      {false};
    bool key_A      {false};
    bool key_S      {false};
    bool key_D      {false};

    bool key_Right  {false};
    bool key_Left   {false};
    bool key_Up     {false};
    bool key_Down   {false};

    bool key_Enter  {false};
    bool key_Space  {false};

    bool key_shift_right {false};
    bool key_shift_left  {false};

    Keyboard_t() = default;
    ~Keyboard_t();

    void restart_keyboard();
};