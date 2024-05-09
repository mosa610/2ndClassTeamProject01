#include "tutorialScene.h"
#include "GameScene.h"
#include "stage.h"
#include "Texture_data.h"

TutorialScene TutorialScene::instance_;
extern int timer;

void TutorialScene::init()
{
    timer = 0;
    stageNumber = 0;
    GameScene::instance()->init();
}

void TutorialScene::deinit()
{
    GameScene::instance()->deinit();
}

void TutorialScene::update()
{
    GameScene::instance()->update();
}

void TutorialScene::draw()
{
    GameLib::clear(1, 0, 1);
    GameScene::instance()->draw();
    reset();
}

void TutorialScene::reset()
{
    GameScene::instance()->reset();
}
    
