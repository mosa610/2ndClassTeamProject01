#include "stage.h"

Stage_script stage01[] = {
    {0,600,30,2,100,true,false,0},     //time,position_x,tex_num,scale,HP,regenerate, texture_transition;
    {100,200,30,2,100,true,false,0},
    {200,400,31,0.5f,80,true,false,1},
    {300,1600,30,2,100,true,false,0},
    {500,1300,32,1,500,false,true,0},
    {800,900,33,1,1000,true,false,1},
    {-1,0,0},       //end
};