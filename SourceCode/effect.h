#pragma once

#include "all.h"
#include "Texture_data.h"

class Effect
{
public:
    int effectTimer = 0;
    VECTOR2 effect_pos = { 0,0 };
    VECTOR2 effect_scale = { 1,1 };
    VECTOR2 effect_texpos = { 0,32 };
    Effect();
    ~Effect();

    void effct_exprosion();
    void effct_fire();
    void effect_draw();
};

