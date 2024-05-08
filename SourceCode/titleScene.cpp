#include "titleScene.h"
#include "GameScene.h"
#include "tutorialScene.h"
#include "Texture_data.h"
#include "mouse.h"

TitleScene TitleScene::instance_;
int timer;
int motion_timer;
TitleMotion** motion;
VECTOR2 play;
VECTOR2 tutorial;
void TitleScene::init()
{
    timer = 0;
    GameLib::texture::load(texture_data[0].tex_num, texture_data[0].filename);
    //motion = new TitleMotion*[5];
    play = { 400,800 };
    tutorial = { 1300,800 };

}

void TitleScene::deinit()
{
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
    GameLib::texture::load(2, back_ground_1[1].filename);
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
       static_cast<float>(GameLib::input::getCursorPosY()) };
    if (TRG(0) & GameLib::input::PAD_START)
    {
        if (cursorPos.x > play.x &&
            cursorPos.y > play.y &&
            cursorPos.x < play.x + 350 &&
            cursorPos.y < play.y + 200)
        {
            changeScene(GameScene::instance());
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
}

void TitleScene::draw()
{
    GameLib::clear(1, 0, 1);
    /*GameLib::texture::begin(1);
    GameLib::texture::draw(1, { 0,0 }, { 1,1 }, { back_ground_1[1].texSize_}, {back_ground_1[timer].maxTexSize_}, {0,0}, 0);
    GameLib::texture::end(1);*/
    GameLib::texture::begin(2);
    GameLib::texture::draw(2, { 0,0 }, { 1,1 }, { back_ground_1[1].texSize_ }, { back_ground_1[timer].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(2);
    GameLib::primitive::rect({ play.x,play.y }, { 350, 200 }, { 50, 50 }, 0, { 1, 0, 0, 1 });
    GameLib::primitive::rect({ tutorial.x,tutorial.y }, { 350, 200 }, { 50, 50 }, 0, { 0, 0, 1, 1 });
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
