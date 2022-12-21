#pragma once

class Game{
    
private:
    Game() = default;
    bool gameStart {false};
    bool fullScreen {false};
public:
    virtual ~Game(){};
    static Game& getInstance();
    void initGame();
    void mainLoop();
};
