#include "stage.h"

Stage_script stage01[] = {
    {0,600,30,2,100,true,false,0},     //time,position_x,tex_num,scale,HP,regenerate, texture_transition, status, weather;
    {10,200,30,2,100,true,false,0},
    {20,400,31,0.5f,100,true,false,1},
    {30,1600,30,2,100,true,false,0},
    {50,1300,32,1,2000,false,true,0},
    {80,900,33,1,1000,true,false,1},
    {-1,0,0},       //end
};