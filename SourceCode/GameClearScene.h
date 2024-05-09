#pragma once

#include "scene.h"

class GameClearScene : public Scene
{
private:
    static GameClearScene instance_;
public:
    static GameClearScene* instance() { return &instance_; }
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
    void reset()override;
private:
    GameClearScene() {}
    GameClearScene(const GameClearScene&) = delete;

private:
    VECTOR2 cursorPos;

    VECTOR2 retryPos;
    VECTOR2 stageSelectPos;
};