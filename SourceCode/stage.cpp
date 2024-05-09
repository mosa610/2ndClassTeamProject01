#include "stage.h"

int stageNumber;

Stage_script stage[4][7] = {
    {
        {0,300,31,0.5f,200,true,false,1},
        {20,700,31,0.5f,200,true,false,1},
        {30,1100,30,2,100,true,false,0},
        {-1,0,0}
    },

    {
        {0,600,30,2,100,true,false,0},     //time, position_x, tex_num, scale, HP, regenerate, texture_transition, status, weather;
        {10,200,30,2,100,true,false,0},
        {20,800,31,0.5f,200,true,false,1},
        {30,1600,34,1,400,true,false,0},
        {-1,0,0}       //end
    },

    {
        {0,900,30,2,50,true,false,0},
        {10,400,31,0.5f,50,true,false,1},
        {20,1400,30,2,50,true,false,0},
        {-1,0,0}
    },

    {
        {0,600,30,2,100,true,false,0},
        {10,400,32,1,1500,true,true,1},
        {20,1000,33,1,1000,true,false,0},
        {40,1400,31,0.5f,100,true,false,1},
        {0,1700,35,0.5f,200,true,false,1},
        
        {-1,0,0}
    }

};

Stage_script stageWeather[4][2] = {
    {
        {30,0,0,0,0,0,0,0,true,Weather::rain}
    },
    {
        {10,0,0,0,0,0,0,0,true,Weather::thunder},
    },
    {
        {60,0,0,0,0,0,0,0,true,Weather::rain}
    }
};

Stage_script stageTime[4][1] = {
    {
        {60,0,0},
    },
    {
        {180,0,0},
    },
    {
        {180,0,0}
    },
    {
        {180,0,0},
    },
};