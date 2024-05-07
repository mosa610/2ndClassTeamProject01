#pragma once

#include "scene.h"

class TutorialScene : public Scene
{
private:
    static TutorialScene instance_;
public:
    static TutorialScene* instance() { return &instance_; }
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
    void reset()override;
private:
    TutorialScene() {}
    TutorialScene(const TutorialScene&) = delete;
};

class TutorialMotion
{
public:
    TutorialMotion(VECTOR2 pos_, VECTOR2 scale_, VECTOR2 tex_pos_, VECTOR2 tex_size_);
public:
    VECTOR2 pos;
    VECTOR2 scale;
    VECTOR2 tex_pos;
    VECTOR2 tex_size;
    int timer;
};