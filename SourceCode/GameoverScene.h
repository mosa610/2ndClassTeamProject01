#pragma once

#include "scene.h"
#include "all.h"
using namespace GameLib::input;

class GameoverScene : public Scene
{
private:
    static GameoverScene instance_;
public:
    static GameoverScene* instance() { return &instance_; }
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
    void reset()override;
private:
    GameoverScene() {}
    GameoverScene(const GameoverScene&) = delete;
    VECTOR2 cursorPos;
};

