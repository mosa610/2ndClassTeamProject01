#pragma once


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
};
// ƒOƒ[ƒoƒ‹‚É‚µ‚Ä‚²‚ß‚ñ
extern int stageNumber;

extern Stage_script stage[][7];

extern Stage_script stageWeather[][1];