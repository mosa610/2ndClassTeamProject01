#include "GameClearScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "mouse.h"
#include "Texture_data.h"

GameClearScene GameClearScene::instance_;

void GameClearScene::init()
{
    GameLib::texture::load(ui[5].tex_num, ui[5].filename);

    retryPos = { 400,800 };
    stageSelectPos = { 1300,800 };
}

void GameClearScene::deinit()
{
    GameLib::texture::release(ui[5].tex_num);
}

void GameClearScene::update()
{
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
       static_cast<float>(GameLib::input::getCursorPosY()) };
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > retryPos.x &&
            cursorPos.y > retryPos.y &&
            cursorPos.x < retryPos.x + 350 &&
            cursorPos.y < retryPos.y + 200)
        {
            changeScene(GameScene::instance());
        }
    }
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > stageSelectPos.x &&
            cursorPos.y > stageSelectPos.y &&
            cursorPos.x < stageSelectPos.x + 350 &&
            cursorPos.y < stageSelectPos.y + 200)
        {
            changeScene(StageSelectScene::instance());
        }
    }
}

void GameClearScene::draw()
{
    GameLib::clear(0, 0, 1);

    GameLib::primitive::rect({ retryPos.x,retryPos.y }, { 350, 200 }, { 50, 50 }, 0, { 1, 0, 0, 1 });
    GameLib::primitive::rect({ stageSelectPos.x,stageSelectPos.y }, { 350, 200 }, { 50, 50 }, 0, { 0, 0, 1, 1 });
    GameLib::texture::begin(ui[5].tex_num);
    GameLib::texture::draw(ui[5].tex_num, { cursorPos }, { 2,2 }, { 0,0 }, { 32,32 }, { 16,16 });
    GameLib::texture::end(ui[5].tex_num);
}

void GameClearScene::reset()
{

}