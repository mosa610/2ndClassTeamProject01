//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"
#include "scene.h"

#include "titleScene.h"
#include "GameScene.h"


//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//--------------------------------------------------------------
//  WinMain�i�G���g���|�C���g�j
//--------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtDumpMemoryLeaks();
    SceneManager sceneManager;
    sceneManager.execute(TitleScene::instance());

    return 0;
}

//******************************************************************************