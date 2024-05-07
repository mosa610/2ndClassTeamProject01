#pragma once

#include "all.h"
#include "Texture_data.h"

class Effect
{
public:
    int effectTimer = 0;
    int effectNum;

    VECTOR2 effect_pos = { 0,0 };
    VECTOR2 effect_scale = { 1,1 };
    VECTOR2 effect_texpos = { 0,32 };
    VECTOR2 effect_texsize = { 0,32 };
    VECTOR2 effect_center = { 16,16 };
    Effect();
    Effect(int timer, VECTOR2 pos, VECTOR2 scale, VECTOR2 texpos, VECTOR2 texsize, VECTOR2 center,int num);
    ~Effect();

    void effct_exprosion();
    void effct_fire();
    void effct_axe();
    void effct_hammer();
    void effct_drill();
    void effct_chainsaw();

    void effect_draw();
};

