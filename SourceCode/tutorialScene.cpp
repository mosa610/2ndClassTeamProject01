#include "tutorialScene.h"
#include "titleScene.h"
#include "GameScene.h"
#include "stage.h"
#include "Texture_data.h"
#include "MusicManager.h"

TutorialScene TutorialScene::instance_;
extern int timer;
VECTOR2 next;
int page = 0;

void TutorialScene::init()
{
    timer = 0;
    stageNumber = 0;
    GameLib::texture::load(ui[5].tex_num, ui[5].filename);
    GameLib::texture::load(back_ground_1[5].tex_num, back_ground_1[5].filename);
    GameLib::texture::load(back_ground_1[6].tex_num, back_ground_1[6].filename);
    GameLib::texture::load(back_ground_1[7].tex_num, back_ground_1[7].filename);
    page = 0;
    next = { 1500,700 };
    nextScene_ = nullptr;
}

void TutorialScene::deinit()
{
    GameLib::texture::release(ui[5].tex_num);
    GameLib::texture::release(back_ground_1[5].tex_num);
    GameLib::texture::release(back_ground_1[6].tex_num);
    GameLib::texture::release(back_ground_1[7].tex_num);
}

void TutorialScene::update()
{
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
       static_cast<float>(GameLib::input::getCursorPosY()) };
    if (TRG(0) & GameLib::input::PAD_START && page == 0)
    {
        if (cursorPos.x > next.x &&
            cursorPos.y > next.y &&
            cursorPos.x < next.x + 350 &&
            cursorPos.y < next.y + 200)
        {
            page = 1;
            MusicManager::Instance().TRG_play(SE::SELECT);
        }
    }
    else if (TRG(0) & GameLib::input::PAD_START && page == 1)
    {
        if (cursorPos.x > next.x &&
            cursorPos.y > next.y &&
            cursorPos.x < next.x + 350 &&
            cursorPos.y < next.y + 200)
        {
            page = 2;
            MusicManager::Instance().TRG_play(SE::SELECT);
        }
    }
    else if (TRG(0) & GameLib::input::PAD_START && page == 2)
    {
        if (cursorPos.x > next.x &&
            cursorPos.y > next.y &&
            cursorPos.x < next.x + 350 &&
            cursorPos.y < next.y + 200)
        {
            MusicManager::Instance().TRG_play(SE::SELECT);
            changeScene(TitleScene::instance());
        }
    }
}

void TutorialScene::draw()
{
    GameLib::clear(1, 0, 1);

    if(page==0)
    {
        GameLib::texture::begin(back_ground_1[5].tex_num);
        GameLib::texture::draw(back_ground_1[5].tex_num, 0, 0, 1, 1, 0, 0, 1920, 1080);
        GameLib::texture::end(back_ground_1[5].tex_num);
    }
    if(page==1)
    {
        GameLib::texture::begin(back_ground_1[6].tex_num);
        GameLib::texture::draw(back_ground_1[6].tex_num, 0, 0, 1, 1, 0, 0, 1920, 1080);
        GameLib::texture::end(back_ground_1[6].tex_num);
    }
    if(page==2)
    {
        GameLib::texture::begin(back_ground_1[7].tex_num);
        GameLib::texture::draw(back_ground_1[7].tex_num, 0, 0, 1, 1, 0, 0, 1920, 1080);
        GameLib::texture::end(back_ground_1[7].tex_num);
    }
    GameLib::primitive::rect({ next.x,next.y }, { 350, 200 }, { 0, 0 }, 0, { 1, 1, 1, 0.6f });

    GameLib::texture::begin(ui[5].tex_num);
    GameLib::texture::draw(ui[5].tex_num, { cursorPos }, { 2,2 }, { 0,0 }, { 32,32 }, { 16,16 });
    GameLib::texture::end(ui[5].tex_num);
    reset();
}

void TutorialScene::reset()
{
}
    
