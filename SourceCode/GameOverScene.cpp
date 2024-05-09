#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "mouse.h"
#include "Texture_data.h"
#include "MusicManager.h"

GameOverScene GameOverScene::instance_;

void GameOverScene::init()
{
    GameLib::texture::load(ui[5].tex_num, ui[5].filename);
    GameLib::texture::load(back_ground_1[3].tex_num, back_ground_1[3].filename);

    retryPos = { 400-50,800 - 50 };
    retirePos = { 1300 - 50,800 - 50 };

    nextScene_ = nullptr;
}

void GameOverScene::deinit()
{
    GameLib::texture::release(ui[5].tex_num);
}

void GameOverScene::update()
{
    MusicManager::Instance().STATE_play(BGM::OVER, false);
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
            MusicManager::Instance().Stop(BGM::OVER);
        }
    }
    if (GameLib::input::TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > retirePos.x &&
            cursorPos.y > retirePos.y &&
            cursorPos.x < retirePos.x + 350 &&
            cursorPos.y < retirePos.y + 200)
        {
            MusicManager::Instance().TRG_play(SE::SELECT);
            changeScene(StageSelectScene::instance());
            MusicManager::Instance().Stop(BGM::OVER);
        }
    }
}

void GameOverScene::draw()
{
    GameLib::clear(0, 0, 1);

    GameLib::texture::begin(back_ground_1[3].tex_num);
    GameLib::texture::draw(back_ground_1[3].tex_num, { 0,0 }, { 1,1 }, { back_ground_1[3].texSize_ }, { back_ground_1[3].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(back_ground_1[3].tex_num);

    GameLib::primitive::rect({ retryPos.x,retryPos.y }, { 350, 200 }, { 0, 0 }, 0, { 1, 1, 1, 0.6f });
    GameLib::text_out(4, "Retry", retryPos.x + 175, retryPos.y + 100, 3, 3, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::primitive::rect({ retirePos.x ,retirePos.y }, { 350, 200 }, { 0, 0 }, 0, { 1, 1, 1, 0.6f });
    GameLib::text_out(4, "stage", retirePos.x + 175, retirePos.y + 60, 3, 3, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::text_out(4, "select", retirePos.x + 175, retirePos.y + 140, 3, 3, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::texture::begin(ui[5].tex_num);
    GameLib::texture::draw(ui[5].tex_num, { cursorPos }, { 2,2 }, { 0,0 }, { 32,32 }, { 16,16 });
    GameLib::texture::end(ui[5].tex_num);
}

void GameOverScene::reset()
{

}