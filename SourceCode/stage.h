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
    int weather;
};
// �O���[�o���ɂ��Ă��߂�
int stage_num;

extern Stage_script stage[][7];