#pragma once
#include "status.h"

struct Stage_script
{
    int time;
    float position_x;
    int tex_num;
    float scale;
    float HP;
    bool regenerate;
    bool texture_transition;
    int status;
    bool weather = false;
    Weather tr = Weather::nornal;
};
// グローバルにしてごめん
extern int stageNumber;

extern Stage_script stage[][7];

extern Stage_script stageWeather[][3];

extern Stage_script stageTime[][1];