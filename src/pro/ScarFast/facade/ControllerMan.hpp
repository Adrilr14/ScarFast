#pragma once

struct Controller_t;

enum class TControllerMan {sfml};

class ControllerMan {

private:
    /** Constructor por defecto privado **/
    ControllerMan();
    Controller_t* m_motor = nullptr;
public:
    ~ControllerMan();
    static ControllerMan& instancia();
    Controller_t& controller();
};