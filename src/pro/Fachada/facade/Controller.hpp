#pragma once

struct Controller_t {
    
    virtual ~Controller_t() = default;
    virtual void createWindow() = 0;
    virtual void run() = 0;
    virtual bool load_Sprites(std::string v) = 0;
};
