#pragma once

#include "scene.h"

class StageSelectScene : public Scene
{
private:
    static StageSelectScene instance_;
public:
    static StageSelectScene* instance() { return &instance_; }
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
    void reset()override;
private:
    StageSelectScene() {}
    StageSelectScene(const StageSelectScene&) = delete;

private:
    VECTOR2 cursorPos;

    VECTOR2 stage01;
    VECTOR2 stage02;
};