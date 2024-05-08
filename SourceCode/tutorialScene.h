#pragma once

#include "scene.h"
#include "all.h"
using namespace GameLib::input;

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
    VECTOR2 cursorPos;
};

