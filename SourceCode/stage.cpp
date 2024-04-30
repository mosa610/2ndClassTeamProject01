#include "stage.h"

Stage_script stage01[] = {
    {0,700,30,2,100,true,false},     //time,position_x,tex_num,scale,HP,regenerate, texture_transition;
    {100,200,30,2,100,true,false},
    {200,500,31,0.5f,80,true,false},
    {300,1600,30,2,100,true,false},
    {500,1300,32,1,200,false,true},
    {-1,0,0},       //end
};