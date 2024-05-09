#pragma once

#include "scene.h"

class GameScene : public Scene
{
private:
    static GameScene instance_;
public:
    static GameScene* instance() { return &instance_; }
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
    void reset()override;
private:
    GameScene() {}
    GameScene(const GameScene&) = delete;
    VECTOR2 cursorPos;

};