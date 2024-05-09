#pragma once

#include "scene.h"

class GameOverScene : public Scene
{
private:
    static GameOverScene instance_;
public:
    static GameOverScene* instance() { return &instance_; }
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
    void reset()override;
private:
    GameOverScene() {}
    GameOverScene(const GameOverScene&) = delete;

private:
    VECTOR2 cursorPos;

    VECTOR2 retryPos;
    VECTOR2 retirePos;
};