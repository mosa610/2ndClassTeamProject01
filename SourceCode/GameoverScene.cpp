#include "GameoverScene.h"
#include "Texture_data.h"

GameoverScene GameoverScene::instance_;
extern int timer;

void GameoverScene::init()
{
    timer = 0;

}

void GameoverScene::deinit()
{
}

void GameoverScene::update()
{

}

void GameoverScene::draw()
{
    GameLib::clear(1, 0, 1);
    GameLib::text_out(0, "GAMEOVER", 960, 500, 3, 3, 1, 0, 0, 1);
    reset();
}

void GameoverScene::reset()
{
}

