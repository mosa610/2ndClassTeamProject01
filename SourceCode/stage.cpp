#include "stage.h"

Stage_script stage01[] = {
    {0,700,30,2,100,true,false},     //time,position_x,tex_num,scale,HP,regenerate, texture_transition;
    {10,200,30,2,100,true,false},
    {20,500,31,0.5f,80,true,false},
    {30,1600,30,2,100,true,false},
    {50,1300,32,1,500,false,true},
    {-1,0,0},       //end
};