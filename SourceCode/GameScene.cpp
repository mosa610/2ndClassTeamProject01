#include "GameScene.h"
#include "GameoverScene.h"
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
int weather;
int weatherTimer = 0;
extern float hage_pos_x;
extern float hage_scale_x;
float hage_texpos_x = 64;
float hage_texpos_y = 0;
float coin_anime = 0;
int coinTimer = 0;
int gameTimer = 0;
std::string gametimer;
std::string cost;

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
    gameTimer = 0;
    for (int i = 50; i < 55; i++)
    {
        GameLib::texture::load(i, effect_data[i - 50].filename);
    }
    GameLib::texture::load(ui[0].tex_num, ui[0].filename);
    GameLib::texture::load(ui[1].tex_num, ui[1].filename);
    GameLib::texture::load(ui[2].tex_num, ui[2].filename);
    GameLib::texture::load(ui[3].tex_num, ui[3].filename);
    GameLib::texture::load(0, back_ground_1[0].filename);
    GameLib::texture::load(ui[5].tex_num, ui[5].filename);
    GameLib::texture::load(ui[6].tex_num, ui[6].filename);
    GameLib::texture::load(ui[7].tex_num, ui[7].filename);

    newEffect(7);

    nextScene_ = nullptr;
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
    GameLib::texture::release(6);
    GameLib::texture::release(7);
    GameLib::texture::release(ui[5].tex_num);
    GameLib::texture::release(ui[6].tex_num);
    GameLib::texture::release(ui[7].tex_num);

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
    if (timer_ >= stage[stageNumber][currentBuildingNum - 1].time * 60 && stage[stageNumber][currentBuildingNum - 1].time >= 0)
    {

        building_[currentBuildingNum - 1] = new building(&stage[stageNumber][currentBuildingNum - 1], stage[stageNumber][currentBuildingNum - 1].position_x,
            stage[stageNumber][currentBuildingNum - 1].tex_num,
            stage[stageNumber][currentBuildingNum - 1].scale,
            stage[stageNumber][currentBuildingNum - 1].HP,
            stage[stageNumber][currentBuildingNum - 1].regenerate,
            currentBuildingNum,
            stage[stageNumber][currentBuildingNum - 1].status);

        currentBuildingNum++;
    }
    for (int i = 0; i < currentBuildingNum - 1; i++)
    {
        for (int j = 0; j < currentItemNum; j++)
        {
            building_[i]->hit(&item_[j], j);
            building_[i]->hageVSBuild(hage_pos_x, 200);
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
    weather = Weather::nornal;
    cloud_pos_x += addSpeed;

    if (cloud_pos_x == 0)
    {
        addSpeed = 0;
        weather = Weather::rain;

        weatherTimer++;
    }
    if (timer_ % 10 < 5)
    {
        rain_pos = 1920;
        hage_texpos_x = 64;
    }
    else
    {
        rain_pos = 0;
        hage_texpos_x = 0;
    }
    if (timer_ % 10 < 5)
    {
        thunder_pos = 1920;
    }
    else
    {
        thunder_pos = 0;
    }
    if (weatherTimer == 1200)
    {
        addSpeed = 4.0f;
        weather == Weather::nornal;
    }

    if (timer_ % 60 == 0) {
        status_.addCurrentCost(1);
        if (plusHP != 0)
        {
            status_.addCurrentCost(plusHP);
            plusHP = 0;
        }
    }
    hage();
    if (timer_ % 30 < 15)
    {
        hage_texpos_x = 64;
    }
    else
    {
        hage_texpos_x = 0;
    }
    if (coinTimer > 56)
    {
        coinTimer = 0;
    }
    coinTimer++;
    coin_anime = 16 * (coinTimer / 4);

    if (timer_ % 60 == 0)
    {
        gameTimer += addTimer;
    }
    if (gameTimer >= 180)
    {
        changeScene(GameOverScene::instance());
    }

    if (acceleration == true && timer_ % 2 != 0)
        timer_++;
    else
    timer_ += addTimer;
}

void GameScene::draw()
{
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
       static_cast<float>(GameLib::input::getCursorPosY()) };
    GameLib::clear(0.2f, 0.2f, 1.0f);
    GameLib::texture::begin(0);
    GameLib::texture::draw(0, { 0,0 }, { 1,1 }, { back_ground_1[0].texSize_ }, { back_ground_1[0].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(0);
    for (int i = 0; i < currentBuildingNum-1; i++)
    {
        if (building_[i])
        {
            building_[i]->draw();
        }
    }
    GameLib::primitive::circle({ hage_pos_x,690 }, 200, { 1,1 }, 0, { 1,0,0,0.5f });
    GameLib::texture::begin(ui[4].tex_num);
    GameLib::texture::draw(ui[4].tex_num, { hage_pos_x,690 }, { -hage_scale_x,2 }, { hage_texpos_x,hage_texpos_y }, { 64,64 }, { 32,32 }, 0, { 1,1,1,1 });
    GameLib::texture::end(ui[4].tex_num);
    for (int i = 0; i < currentItemNum; i++)
    {
        item_[i].draw();
    }
    if (weather == Weather::rain)
    {
        GameLib::texture::begin(ui[2].tex_num);
        GameLib::texture::draw(ui[2].tex_num, { cloud_pos_x,0 }, { 1,1 }, { rain_pos,0 }, { 1920,1080 }, { 0,0 }, 0);
        GameLib::texture::end(ui[2].tex_num);
        GameLib::texture::begin(ui[7].tex_num);
        GameLib::texture::draw(ui[7].tex_num, { 800,900 }, { 2,2 }, { 0,0 }, { 64,64 }, { 32,32 }, 0);
        GameLib::texture::end(ui[7].tex_num);
        GameLib::texture::begin(ui[7].tex_num);
        GameLib::texture::draw(ui[7].tex_num, { 1700,900 }, { 2,2 }, { 0,0 }, { 64,64 }, { 32,32 }, 0);
        GameLib::texture::end(ui[7].tex_num);
    }
    if (weather == Weather::thunder)
    {
        GameLib::texture::begin(ui[3].tex_num);
        GameLib::texture::draw(ui[3].tex_num, { 0,0 }, { 1,1 }, { thunder_pos,0 }, { 1920,1080 }, { 0,0 }, 0);
        GameLib::texture::end(ui[3].tex_num);
        GameLib::texture::begin(ui[7].tex_num);
        GameLib::texture::draw(ui[7].tex_num, { 500,900 }, { 2,2 }, { 0,0 }, { 64,64 }, { 32,32 }, 0);
        GameLib::texture::end(ui[7].tex_num);
        GameLib::texture::begin(ui[7].tex_num);
        GameLib::texture::draw(ui[7].tex_num, { 1400,900 }, { 2,2 }, { 0,0 }, { 64,64 }, { 32,32 }, 0);
        GameLib::texture::end(ui[7].tex_num);
    }
    GameLib::texture::begin(ui[0].tex_num);
    GameLib::texture::draw(ui[0].tex_num, { cloud_pos_x,0 }, { 1,1 }, { 0,0 }, { 1920,360 }, { 0,0 }, 0);
    GameLib::texture::end(ui[0].tex_num);
    GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
    GameLib::primitive::rect({ SCREEN_W - 130,10 }, { ui[0].maxTexSize_.x * 0.2f +5,ui[0].maxTexSize_.y * 0.2f + 5 }, { 0,0 }, 0, { 0,0,0,1 });
    GameLib::texture::begin(ui[1].tex_num);
    GameLib::texture::draw(ui[1].tex_num, { SCREEN_W - 130,10 }, { 0.2f,0.2f }, { ui[0].texSize_ }, { ui[0].maxTexSize_ }, { 0,0 }, 0, { 0, 1, 0, UI_A });
    GameLib::texture::end(ui[1].tex_num);
    GameLib::texture::begin(ui[5].tex_num);
    GameLib::texture::draw(ui[5].tex_num, { cursorPos }, { 2,2 }, { 0,0 }, { 32,32 }, { 16,16 });
    GameLib::texture::end(ui[5].tex_num);
    GameLib::texture::begin(ui[6].tex_num);
    GameLib::texture::draw(ui[6].tex_num, { 80,80 }, { 7,7 }, { coin_anime,0 }, { 16,16 }, { 8,8 });
    GameLib::texture::end(ui[6].tex_num);
    cost = std::to_string(status_.getCost());
    GameLib::text_out(1, cost, 150, 40, 3, 3, 1, 1, 1, 1);

    gametimer = std::to_string(gameTimer);
    GameLib::text_out(1, gametimer, 900, 40, 3, 3, 1, 1, 1, 1);
    GameLib::debug::setString("stage_num%d", stageNumber);

}

void GameScene::reset()
{

}
