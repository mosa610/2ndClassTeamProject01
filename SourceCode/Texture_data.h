#pragma once
#include "all.h"

struct Texture_data
{
    int tex_num;
    wchar_t* filename;
    VECTOR2 texSize_;
    VECTOR2 maxTexSize_;
    bool load = false;
};

extern Texture_data texture_data[];
extern Texture_data back_ground[];
extern Texture_data effect_data[];

