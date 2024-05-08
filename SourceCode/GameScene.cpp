#include "GameScene.h"
#include "mouse.h"
#include "status.h"
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
status status_;
int status::current_cost;
bool acceleration = false;
float UI_A = 0.4f;
int addTimer = 1;
int addSpeed = 4.0f;
float cloud_pos_x = -1920;
float rain_pos = 0;
float thunder_pos = 0;
extern int plusHP;

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
    GameLib::texture::load(ui[0].tex_num, ui[0].filename);
    GameLib::texture::load(ui[1].tex_num, ui[1].filename);
    GameLib::texture::load(ui[2].tex_num, ui[2].filename);
    GameLib::texture::load(ui[3].tex_num, ui[3].filename);
    GameLib::texture::load(0, back_ground[0].filename);
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
    GameLib::texture::release(0);
}

void GameScene::update()
{
    Mouse::instance()->setPosition();
    VECTOR2 mouse_pos;
    mouse_pos = Mouse::instance()->getPosition();
    if (mouse_pos.x > SCREEN_W - 130 &&
        mouse_pos.x < SCREEN_W - 130 + (ui[0].maxTexSize_.x * 0.2f + 5) &&
        mouse_pos.y > 10 &&
        mouse_pos.y < 10 + (ui[0].maxTexSize_.y * 0.2f + 5))
    {
        if (TRG_RELEASE(0) & GameLib::input::PAD_START)
        {
            if (acceleration) {
                acceleration = false;
                UI_A = 0.4f;
                addTimer = 1;
            }
            else {
                acceleration = true;
                UI_A = 1.0f;
                addTimer = 2;
            }
        }
    }
    if (timer_ >= stage01[currentBuildingNum - 1].time * 60 && stage01[currentBuildingNum - 1].time >= 0)
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

    cloud_pos_x += addSpeed;
    
    if (cloud_pos_x == 0)
    {
        addSpeed = 0;
        if (timer_ % 10 < 5)
        {
            rain_pos = 1920;
        }
        else
        {
            rain_pos = 0;
        }
        /*if (timer_ % 10 < 5)
        {
            thunder_pos = 1920;
        }
        else
        {
            thunder_pos = 0;
        }*/
    }
    if (timer_ % 60 == 0) {
        status_.addCurrentCost(1);
        if (plusHP != 0)
        {
            status_.addCurrentCost(plusHP);
            plusHP = 0;
        }
    }
    if (acceleration == true && timer_ % 2 != 0)
        timer_++;
    else
    timer_ += addTimer;
}

void GameScene::draw()
{
    GameLib::clear(0.2f, 0.2f, 1.0f);
    GameLib::texture::begin(0);
    GameLib::texture::draw(0, { 0,0 }, { 1,1 }, { back_ground[0].texSize_ }, { back_ground[0].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(0);
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
    if (cloud_pos_x == 0)
    {
        GameLib::texture::begin(ui[2].tex_num);
        GameLib::texture::draw(ui[2].tex_num, { 0,0 }, { 1,1 }, { rain_pos,0 }, { 1920,1080 }, { 0,0 }, 0);
        GameLib::texture::end(ui[2].tex_num);
        /*GameLib::texture::begin(ui[3].tex_num);
        GameLib::texture::draw(ui[3].tex_num, { 0,0 }, { 1,1 }, { thunder_pos,0 }, { 1920,1080 }, { 0,0 }, 0);
        GameLib::texture::end(ui[3].tex_num);*/
    }
    GameLib::texture::begin(ui[0].tex_num);
    GameLib::texture::draw(ui[0].tex_num, { cloud_pos_x,0 }, { 1,1 }, { 0,0 }, { 1920,360 }, { 0,0 }, 0);
    GameLib::texture::end(ui[0].tex_num);
    GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
    GameLib::primitive::rect({ SCREEN_W - 130,10 }, { ui[0].maxTexSize_.x * 0.2f +5,ui[0].maxTexSize_.y * 0.2f + 5 }, { 0,0 }, 0, { 0,0,0,1 });
    GameLib::texture::begin(ui[1].tex_num);
    GameLib::texture::draw(ui[1].tex_num, { SCREEN_W - 130,10 }, { 0.2f,0.2f }, { ui[0].texSize_ }, { ui[0].maxTexSize_ }, { 0,0 }, 0, { 0, 1, 0, UI_A });
    GameLib::texture::end(ui[1].tex_num);
}

void GameScene::reset()
{
}
