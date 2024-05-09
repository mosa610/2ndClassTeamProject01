#include "StageSelectScene.h"
#include "GameScene.h"
#include "mouse.h"
#include "stage.h"
#include "Texture_data.h"

StageSelectScene StageSelectScene::instance_;

void StageSelectScene::init()
{
    stageNumber = -1;
    GameLib::texture::load(ui[5].tex_num, ui[5].filename);
    GameLib::texture::load(back_ground_1[2].tex_num, back_ground_1[2].filename);

    stage01 = { 400,800 };
    stage02 = { 1300,800 };

    nextScene_ = nullptr;
}

void StageSelectScene::deinit()
{
    GameLib::texture::release(back_ground_1[2].tex_num);
    GameLib::texture::release(ui[5].tex_num);
}

void StageSelectScene::update()
{
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
       static_cast<float>(GameLib::input::getCursorPosY()) };
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > stage01.x &&
            cursorPos.y > stage01.y &&
            cursorPos.x < stage01.x + 350 &&
            cursorPos.y < stage01.y + 200)
        {
            stageNumber = 1;
            changeScene(GameScene::instance());
        }
    }
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > stage02.x &&
            cursorPos.y > stage02.y &&
            cursorPos.x < stage02.x + 350 &&
            cursorPos.y < stage02.y + 200)
        {
            stageNumber = 2;
            changeScene(GameScene::instance());
        }
    }
}

void StageSelectScene::draw()
{
    GameLib::clear(1, 0, 1);

    GameLib::texture::begin(back_ground_1[2].tex_num);
    GameLib::texture::draw(back_ground_1[2].tex_num, { 0,0 }, { 1,1 }, { back_ground_1[2].texSize_ }, { back_ground_1[2].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(back_ground_1[2].tex_num);

    GameLib::primitive::rect({ stage01.x,stage01.y }, { 350, 200 }, { 50, 50 }, 0, { 1, 0, 0, 1 });
    GameLib::primitive::rect({ stage02.x,stage02.y }, { 350, 200 }, { 50, 50 }, 0, { 0, 0, 1, 1 });
    GameLib::texture::begin(ui[5].tex_num);
    GameLib::texture::draw(ui[5].tex_num, { cursorPos }, { 2,2 }, { 0,0 }, { 32,32 }, { 16,16 });
    GameLib::texture::end(ui[5].tex_num);
}

void StageSelectScene::reset()
{

}