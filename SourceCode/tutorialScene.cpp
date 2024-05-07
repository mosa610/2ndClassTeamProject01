#include "tutorialScene.h"
#include "Texture_data.h"

TutorialScene TutorialScene::instance_;
int timer;
int motion_timer;
TutorialMotion** motion;

void TutorialScene::init()
{
    timer = 0;
    GameLib::texture::load(texture_data[0].tex_num, texture_data[0].filename);
    motion = new TutorialMotion * [5];

}

void TutorialScene::deinit()
{
}

void TutorialScene::update()
{
    if (motion_timer % 60 == 59 && motion_timer / 60 < 5)
    {
        motion[motion_timer / 60] = new TutorialMotion({ 100,0 }, { 1,1 }, { 0,0 }, { texture_data[0].maxTexSize_ });
    }
    GameLib::texture::load(1, back_ground[timer].filename);
    timer++;
    if (timer >= 60) timer = 0;
    motion_timer++;
}

void TutorialScene::draw()
{
    GameLib::clear(1, 0, 1);
    GameLib::texture::begin(1);
    GameLib::texture::draw(1, { 0,0 }, { 1,1 }, { back_ground[timer].texSize_ }, { back_ground[timer].maxTexSize_ }, { 0,0 }, 0);
    GameLib::texture::end(1);

    reset();
}

void TutorialScene::reset()
{
    GameLib::texture::release(1);
    GameLib::texture::release(texture_data[0].tex_num);
}

TutorialMotion::TutorialMotion(VECTOR2 pos_, VECTOR2 scale_, VECTOR2 tex_pos_, VECTOR2 tex_size_)
{
    pos = pos_;
    scale = scale_;
    tex_pos = tex_pos_;
    tex_size = tex_size_;
}
