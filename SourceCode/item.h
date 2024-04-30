#pragma once
#include "status.h"
#include "scene.h"
#include "all.h"

using namespace GameLib::input;

class ItemUI : public UI
{
public:
    bool enterUi;
    bool a;
    ItemUI()
    {
        width_height = { 200,200 };
    }
};

static enum ItemNo
{
    AXE,
    CHAINSAW,
    FIRE,
    HAMMER,
    DRILL,
    DYNAMITE,
    item_end
}itemno;

class Item : public status
{
public:
    Item();
    ~Item();
public:
    void update();
    void draw();

    void Enter();

    void Axe();
    void Chainsaw();
    void Fire();

    void Hammer();
    void Drill();
    void Dynamite();

    ItemUI* ItemUIManager();
    ItemNo* ItemNoManager() { return &itemno; }
    int getAttack() { return atk; }
    void setAttack(int attack) { atk = attack; }
    int getCost() { return cost; }
    void setCost(int cost_) { cost = cost_; }


private:
    int atk;
    bool useItem;
    bool enter;
    VECTOR2 cursorPos;
    VECTOR4 color;
};

