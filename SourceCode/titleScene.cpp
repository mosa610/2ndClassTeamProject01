#include "titleScene.h"
#include "GameScene.h"
#include "StageSelectScene.h"
#include "tutorialScene.h"
#include "Texture_data.h"
#include "mouse.h"
#include "MusicManager.h"

TitleScene TitleScene::instance_;
int timer;
int motion_timer;
TitleMotion** motion;
VECTOR2 play;
VECTOR2 tutorial;
extern int stageNumber;


void TitleScene::init()
{
    timer = 0;
    GameLib::texture::load(texture_data[0].tex_num, texture_data[0].filename);
    GameLib::texture::load(back_ground_1[1].tex_num, back_ground_1[1].filename);
    GameLib::texture::load(ui[5].tex_num, ui[5].filename);
    //motion = new TitleMotion*[5];
    play = { 400-50,800-50 };
    tutorial = { 1300-50,800-50 };
    nextScene_ = nullptr;
}

void TitleScene::deinit()
{
    GameLib::texture::release(back_ground_1[1].tex_num);
    GameLib::texture::release(ui[5].tex_num);
}

void TitleScene::update()
{
   /* if (motion_timer % 60 == 59&& motion_timer / 60 <5)
    {
        motion[motion_timer / 60+1] = new TitleMotion({ 100,0 }, { 1,1 }, { 0,0 }, { texture_data[0].maxTexSize_ });
    }
    GameLib::texture::load(1, back_ground[timer].filename);
    timer++;
    if (timer >= 60) timer = 0;
    motion_timer++;*/
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
       static_cast<float>(GameLib::input::getCursorPosY()) };
    if (TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > play.x &&
            cursorPos.y > play.y &&
            cursorPos.x < play.x + 350 &&
            cursorPos.y < play.y + 200)
        {
            changeScene(StageSelectScene::instance());
        }
    }
    if (TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > tutorial.x &&
            cursorPos.y > tutorial.y &&
            cursorPos.x < tutorial.x + 350 &&
            cursorPos.y < tutorial.y + 200)
        {
            changeScene(TutorialScene::instance());
        }
    }

    MusicManager::Instance().STATE_play(BGM::TITLE, true);
}

void TitleScene::draw()
{
    GameLib::clear(1, 0, 1);
    /*GameLib::texture::begin(1);
    GameLib::texture::draw(1, { 0,0 }, { 1,1 }, { back_ground_1[1].texSize_}, {back_ground_1[timer].maxTexSize_}, {0,0}, 0);
    GameLib::texture::end(1);*/
    GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
    GameLib::texture::begin(back_ground_1[1].tex_num);
    GameLib::texture::draw(back_ground_1[1].tex_num, { 0,0 }, { 1,1 }, { back_ground_1[1].texSize_ }, { back_ground_1[timer].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(back_ground_1[1].tex_num);
    GameLib::primitive::rect({ play.x,play.y }, { 350, 200 }, { 0, 0 }, 0, { 1, 1, 1, 0.6f });
    GameLib::text_out(4, "play", play.x + 175, play.y + 100, 4, 4, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::primitive::rect({ tutorial.x,tutorial.y }, { 350, 200 }, { 0, 0 }, 0, { 1, 1, 1, 0.6f });
    GameLib::text_out(4, "tuto", tutorial.x + 175, tutorial.y + 60, 4, 4, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);
    GameLib::text_out(4, "rial", tutorial.x + 175, tutorial.y + 140, 4, 4, 0, 0, 0, 1, GameLib::TEXT_ALIGN::MIDDLE);

    GameLib::texture::begin(ui[5].tex_num);
    GameLib::texture::draw(ui[5].tex_num, { cursorPos }, { 2,2 }, { 0,0 }, { 32,32 }, { 16,16 });
    GameLib::texture::end(ui[5].tex_num);
    reset();
}

void TitleScene::reset()
{
    GameLib::texture::release(1);
    GameLib::texture::release(texture_data[0].tex_num);
}

TitleMotion::TitleMotion(VECTOR2 pos_, VECTOR2 scale_, VECTOR2 tex_pos_, VECTOR2 tex_size_)
{
    pos = pos_;
    scale = scale_;
    tex_pos = tex_pos_;
    tex_size = tex_size_;
}
