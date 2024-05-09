#include "GameClearScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "mouse.h"
#include "Texture_data.h"
#include "MusicManager.h"

GameClearScene GameClearScene::instance_;

void GameClearScene::init()
{
    GameLib::texture::load(ui[5].tex_num, ui[5].filename);
    GameLib::texture::load(back_ground_1[4].tex_num, back_ground_1[4].filename);

    retryPos = { 400,800 };
    stageSelectPos = { 1300,800 };

    nextScene_ = nullptr;
}

void GameClearScene::deinit()
{
    GameLib::texture::release(ui[5].tex_num);
}

void GameClearScene::update()
{
    MusicManager::Instance().STATE_play(BGM::CLEAR, true);
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
       static_cast<float>(GameLib::input::getCursorPosY()) };
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > retryPos.x &&
            cursorPos.y > retryPos.y &&
            cursorPos.x < retryPos.x + 350 &&
            cursorPos.y < retryPos.y + 200)
        {
            MusicManager::Instance().TRG_play(SE::SELECT);
            changeScene(GameScene::instance());
            MusicManager::Instance().Stop(BGM::CLEAR);
        }
    }
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > stageSelectPos.x &&
            cursorPos.y > stageSelectPos.y &&
            cursorPos.x < stageSelectPos.x + 350 &&
            cursorPos.y < stageSelectPos.y + 200)
        {
            MusicManager::Instance().TRG_play(SE::SELECT);
            changeScene(StageSelectScene::instance());
            MusicManager::Instance().Stop(BGM::CLEAR);
        }
    }
}

void GameClearScene::draw()
{
    GameLib::clear(0, 0, 1);

    GameLib::texture::begin(back_ground_1[4].tex_num);
    GameLib::texture::draw(back_ground_1[4].tex_num, { 0,0 }, { 1,1 }, { back_ground_1[4].texSize_ }, { back_ground_1[4].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(back_ground_1[4].tex_num);

    GameLib::primitive::rect({ retryPos.x,retryPos.y }, { 350, 200 }, { 0,0 }, 0, { 1, 1, 1, 0.6f });
    GameLib::text_out(4, "Retry", retryPos.x + 175, retryPos.y + 100, 3, 3, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::primitive::rect({ stageSelectPos.x,stageSelectPos.y }, { 350, 200 }, { 0,0 }, 0, { 1, 1, 1, 0.6f });
    GameLib::text_out(4, "stage", stageSelectPos.x + 175, stageSelectPos.y + 60, 3, 3, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::text_out(4, "select", stageSelectPos.x + 175, stageSelectPos.y + 140, 3, 3, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::texture::begin(ui[5].tex_num);
    GameLib::texture::draw(ui[5].tex_num, { cursorPos }, { 2,2 }, { 0,0 }, { 32,32 }, { 16,16 });
    GameLib::texture::end(ui[5].tex_num);
}


void GameClearScene::reset()
{

}