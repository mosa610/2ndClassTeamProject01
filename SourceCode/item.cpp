#include "item.h"
#include "mouse.h"


ItemUI* itemUi;
int drag_con[6];

Item::Item()
{
    GameLib::texture::load(10, L"./Data/Images/06 Border 01.png");
    GameLib::texture::load(11, L"./Data/Images/dynamite.png");
    GameLib::texture::load(12, L"./Data/Images/Armi Black png.png");
    GameLib::texture::load(13, L"./Data/Images/Campfire36.png");
    GameLib::texture::load(14, L"./Data/Images/dril.png");
    GameLib::texture::load(15, L"./Data/Images/chainsaw.png");
    color = { 1,0,0,1 };
    atk = 0;
    useItem = false;
    itemUi = new ItemUI[ItemNo::item_end];
    itemUi[ItemNo::AXE].position = { 200,928 };
    itemUi[ItemNo::CHAINSAW].position = { 500,900 };
    itemUi[ItemNo::FIRE].position = { 800,900 };
    itemUi[ItemNo::HAMMER].position = { 1104,928 };
    itemUi[ItemNo::DRILL].position = { 1400,900 };
    itemUi[ItemNo::DYNAMITE].position = { 1700,900 };
    for (int i = 0; i < ItemNo::item_end; ++i)
    {
        drag_con[i] = 0;
    }
}
Item::~Item()
{
    GameLib::texture::release(10);
    GameLib::texture::release(11);
    GameLib::texture::release(12);
    GameLib::texture::release(13);
    GameLib::texture::release(14);
    GameLib::texture::release(15);

    delete[] itemUi;
}

void Item::update()
{
    Mouse::instance()->setPosition();

    for (int i = 0; i < ItemNo::item_end; ++i)
    {
        
            if (STATE(0) & GameLib::input::PAD_START && itemUi[i].a == true || drag_con[i] == 1)
            {
                itemUi[i].position = cursorPos;
                drag_con[i] = 1;
            }
            if (TRG_RELEASE(0) & GameLib::input::PAD_START)
            {
                itemUi[ItemNo::AXE].position = { 200,928 };
                itemUi[ItemNo::CHAINSAW].position = { 500,900 };
                itemUi[ItemNo::FIRE].position = { 800,900 };
                itemUi[ItemNo::HAMMER].position = { 1104,928 };
                itemUi[ItemNo::DRILL].position = { 1400,900 };
                itemUi[ItemNo::DYNAMITE].position = { 1700,900 };
                drag_con[i] = 0;
            }
        

    }
    Enter();
}

void Item::draw()
{
    GameLib::texture::begin(10);
    GameLib::texture::draw(10, { 200, 900 }, { 3, 3 }, { 192,192 }, { 64,64 }, { 32,32 }, 0);
    GameLib::texture::end(10);
    GameLib::texture::begin(10);
    GameLib::texture::draw(10, { 500, 900 }, { 3, 3 }, { 192,192 }, { 64,64 }, { 32,32 }, 0);
    GameLib::texture::end(10);
    GameLib::texture::begin(10);
    GameLib::texture::draw(10, { 800, 900 }, { 3, 3 }, { 192,192 }, { 64,64 }, { 32,32 }, 0);
    GameLib::texture::end(10);
    GameLib::texture::begin(10);
    GameLib::texture::draw(10, { 1100, 900 }, { 3, 3 }, { 192,192 }, { 64,64 }, { 32,32 }, 0);
    GameLib::texture::end(10);
    GameLib::texture::begin(10);
    GameLib::texture::draw(10, { 1400, 900 }, { 3, 3 }, { 192,192 }, { 64,64 }, { 32,32 }, 0);
    GameLib::texture::end(10);
    GameLib::texture::begin(10);
    GameLib::texture::draw(10, { 1700, 900 }, { 3, 3 }, { 192,192 }, { 64,64 }, { 32,32 }, 0);
    GameLib::texture::end(10);
    GameLib::texture::begin(12);
    GameLib::texture::draw(12, { itemUi[ItemNo::AXE].position }, { 3, 3 }, { 124,0 }, { 52,64 }, { 32,32 }, 0);
    GameLib::texture::end(12);
    GameLib::texture::begin(12);
    GameLib::texture::draw(12, { itemUi[ItemNo::HAMMER].position }, { 3, 3 }, { 388,0 }, { 52,64 }, { 32,32 }, 0);
    GameLib::texture::end(12);
    GameLib::texture::begin(11);
    GameLib::texture::draw(11, { itemUi[ItemNo::DYNAMITE].position }, { 5,5 }, { 0,0 }, { 32,32 }, { 16,16 }, 0);
    GameLib::texture::end(11);
    GameLib::texture::begin(13);
    GameLib::texture::draw(13, { itemUi[ItemNo::FIRE].position }, { 6,6 }, { 0,0 }, { 32,32 }, { 16,16 }, 0);
    GameLib::texture::end(13);
    GameLib::texture::begin(14);
    GameLib::texture::draw(14, { itemUi[ItemNo::DRILL].position }, { 4,4 }, { 0,0 }, { 32,32 }, { 16,16 }, 0);
    GameLib::texture::end(14);
    GameLib::texture::begin(15);
    GameLib::texture::draw(15, { itemUi[ItemNo::CHAINSAW].position }, { 4,4 }, { 0,0 }, { 32,32 }, { 16,16 }, 0);
    GameLib::texture::end(15);
    GameLib::debug::setString("cursor%d", GameLib::input::getCursorPosX());
    GameLib::debug::setString("cursor%d", GameLib::input::getCursorPosY());
    GameLib::debug::setString("drag%d", drag_con[0]);

}

void Item::Enter()
{
    cursorPos = { static_cast<float>(GameLib::input::getCursorPosX()),
        static_cast<float>(GameLib::input::getCursorPosY()) };
    for (int i = 0; i < ItemNo::item_end; ++i)
    {
        itemUi[i].enterUi = false;
        if (cursorPos.x > itemUi[i].position.x - itemUi[i].width_height.x / 2 &&
            cursorPos.y > itemUi[i].position.y - itemUi[i].width_height.y / 2 &&
            cursorPos.x < itemUi[i].position.x + itemUi[i].width_height.x / 2 &&
            cursorPos.y < itemUi[i].position.y + itemUi[i].width_height.y / 2)
        {
            if (TRG(0) & GameLib::input::PAD_START)
            {
                itemUi[i].a = true;
            }
            itemUi[i].enterUi = true;
        }
        if (TRG_RELEASE(0) & GameLib::input::PAD_START)
        {
            itemUi[i].a = false;
            drag_con[i] = 0;
        }
    }

}

void Item::Axe()
{
    atk = 20;
    cost = 5;
}

void Item::Chainsaw()
{
    atk = 50;
    cost = 20;
}

void Item::Fire()
{
    atk = 100;
    cost = 40;
}

void Item::Hammer()
{
    atk = 20;
    cost = 5;
}

void Item::Drill()
{
    atk = 50;
    cost = 20;
}

void Item::Dynamite()
{
    atk = 100;
    cost = 40;
}

ItemUI* Item::ItemUIManager()
{
    return itemUi;
}
