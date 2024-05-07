#include "GameScene.h"
#include "building.h"
#include "item.h"
#include "stage.h"
#include <time.h>
#include "effect.h"



GameScene GameScene::instance_;

int itemNum = 0;
int buildingNum = 0;
int currentBuildingNum;
int currentItemNum;
building** building_;
Item* item_;
Effect** effect;


void GameScene::init()
{
    srand(time(0));
    currentBuildingNum = 1;
    buildingNum = 6;
    building_ = new building*[buildingNum];
    currentItemNum = 1;
    itemNum = 1;
    item_ = new Item[itemNum];
    effect = new Effect*[buildingNum];
    for (int i = 50; i < 55; i++)
    {
        GameLib::texture::load(i, effect_data[i - 50].filename);
    }
    newEffect();
}

void GameScene::deinit()
{
    for (int i = 0; i < currentBuildingNum-1; i++)
    {
        delete building_[i];
    }
    delete[] building_;
    delete[] item_;
    delete[] effect;
    GameLib::texture::release(50);
    GameLib::texture::release(51);
    GameLib::texture::release(52);
    GameLib::texture::release(53);
    GameLib::texture::release(54);
}

void GameScene::update()
{
    if (timer_ >= stage01[currentBuildingNum - 1].time&&stage01[currentBuildingNum - 1].time>=0)
    {

        building_[currentBuildingNum - 1] = new building(&stage01[currentBuildingNum - 1], stage01[currentBuildingNum - 1].position_x,
            stage01[currentBuildingNum - 1].tex_num,
            stage01[currentBuildingNum - 1].scale,
            stage01[currentBuildingNum - 1].HP,
            stage01[currentBuildingNum - 1].regenerate,
            currentBuildingNum,
            stage01[currentBuildingNum - 1].status);

        currentBuildingNum++;
    }
    for (int i = 0; i < currentBuildingNum - 1; i++)
    {
        for (int j = 0; j < currentItemNum; j++)
        {
            building_[i]->hit(&item_[j], j);
        }
    }
    for (int i = 0; i < currentBuildingNum-1; i++)
    {
        if (building_[i])
        {
            building_[i]->update();
        }
    }
    for (int i = 0; i < currentItemNum; i++)
    {
        item_[i].update();
    }

    timer_++;
}

void GameScene::draw()
{
    GameLib::clear(0.2f, 0.2f, 1.0f);
    for (int i = 0; i < currentBuildingNum-1; i++)
    {
        if (building_[i])
        {
            building_[i]->draw();
        }
    }
    for (int i = 0; i < currentItemNum; i++)
    {
        item_[i].draw();
    }
}

void GameScene::reset()
{
}
