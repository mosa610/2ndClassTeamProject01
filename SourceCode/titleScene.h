#pragma once

#include "scene.h"

class TitleScene : public Scene
{
private:
    static TitleScene instance_;
public:
    static TitleScene* instance() { return &instance_; }
    void init()override;
    void deinit()override;
    void update()override;
    void draw()override;
    void reset()override;
private:
    TitleScene() {}
    TitleScene(const TitleScene&) = delete;
};

class TitleMotion
{
public:
    TitleMotion(VECTOR2 pos_, VECTOR2 scale_, VECTOR2 tex_pos_, VECTOR2 tex_size_);
public:
    VECTOR2 pos;
    VECTOR2 scale;
    VECTOR2 tex_pos;
    VECTOR2 tex_size;
    int timer;
};