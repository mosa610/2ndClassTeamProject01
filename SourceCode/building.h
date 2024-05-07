#pragma once
#include "status.h"
#include <DirectXMath.h>
#include "item.h"
#include "stage.h"

void newEffect();

class building
{
public:
    building();
    building(Stage_script* stage, float position_x, int tex_num, float scale_, float hp, bool regenerate_, int build_num, int status);
    ~building();
public:
    void update();
    void draw();

    void hit(Item* item, int current_item);

    std::list<building> Building;
private:
    VECTOR2 position;
    VECTOR2 scale;
    VECTOR2 texSize;
    VECTOR2 maxTexSize;
    VECTOR2 nowTexSize;
    VECTOR4 color;
    float MAX_HP;
    float HP;
    int texNum;
    int timer;
    float s;
    float color_timer;
    bool regenerate;
    bool break_build;
    bool texture_transition;
    int break_timer;
    bool effct_anime;
    int effectanimeNum;
    int buildStatus;
    Attribute attribute;
};