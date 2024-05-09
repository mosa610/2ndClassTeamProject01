#include "stage.h"

int stageNumber;

Stage_script stage[3][7] = {
    {
        {0,200,30,2,100,true,false,0},
        {0,400,31,0.5f,100,true,false,1},
        {15,600,32,1,1500,true,true,1},
        {30,1100,33,1,700,true,false,0},
         {-1,0,0}

    },

    {
        {0,600,30,2,100,true,false,0},     //time, position_x, tex_num, scale, HP, regenerate, texture_transition, status, weather;
        {10,200,30,2,100,true,false,0},
        {20,400,31,0.5f,100,true,false,1},
        {30,1600,30,2,100,true,false,0},
        {50,1300,32,1,1500,false,true,1},
        {80,900,33,1,700,true,false,0},
        {-1,0,0}       //end
    },

    {
        {0,900,30,2,50,true,false,0},
        {10,400,31,0.5f,50,true,false,1},
        {20,1400,30,2,50,true,false,0},
        {-1,0,0}
    }
};

Stage_script stageWeather[3][1] = {
    {
        {-1,0,0}
    },
    {
        {40,0,0,0,0,0,0,0,true}
    },
    {
        {-1,0,0}
    },
};

Stage_script stageTime[3][1] = {
    {
        {180,0,0}
    },
    {
        {180,0,0},
    },
    {
        {180,0,0}
    },
};