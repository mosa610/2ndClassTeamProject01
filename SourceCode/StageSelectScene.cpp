#include "StageSelectScene.h"
#include "GameScene.h"
#include "mouse.h"
#include "stage.h"

StageSelectScene StageSelectScene::instance_;

void StageSelectScene::init()
{
    stage_num = -1;

    stage01 = { 400,800 };
    stage02 = { 1300,800 };
}

void StageSelectScene::deinit()
{

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
            stage_num = 0;
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
            stage_num = 1;
            changeScene(GameScene::instance());
        }
    }
}

void StageSelectScene::draw()
{
    GameLib::clear(1, 0, 1);

    GameLib::primitive::rect({ stage01.x,stage01.y }, { 350, 200 }, { 50, 50 }, 0, { 1, 0, 0, 1 });
    GameLib::primitive::rect({ stage02.x,stage02.y }, { 350, 200 }, { 50, 50 }, 0, { 0, 0, 1, 1 });
}

void StageSelectScene::reset()
{

}