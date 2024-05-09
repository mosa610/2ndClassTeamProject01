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
}

void TutorialScene::deinit()
{
}

void TutorialScene::update()
{
}

void TutorialScene::draw()
{
    GameLib::clear(1, 0, 1);
    reset();
}

void TutorialScene::reset()
{
}
    
