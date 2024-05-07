#include "all.h"
#include "building.h"
#include "stage.h"
#include "Texture_data.h"
#include "effect.h"

int hp;
Effect** effect_;
int effectNum;
static int currentEffectNum;
int itemStatus;


building::building()
{
    GameLib::texture::load(30, texture_data[0].filename);
    scale = { 2,2 };
    texSize = { -48,0 };
    maxTexSize = { 48,125 };
    position.x = rand() % 1280;
    position.y = 1000;
    timer = 0;
}

building::building(Stage_script* stage, float position_x, int tex_num,float scale_,float hp, bool regenerate_, int build_num, int status)
{
    if (texture_data[tex_num - 30].load == false)
    {
        GameLib::texture::load(texture_data[tex_num - 30].tex_num, texture_data[tex_num - 30].filename);
        texture_data[tex_num - 30].load = true;
    }
    position = { position_x,750 };
    texNum = tex_num;
    texSize = { texture_data[texNum - 30].texSize_.x,
        texture_data[texNum - 30].texSize_.y };
    nowTexSize = { texture_data[texNum - 30].maxTexSize_.x,
        texture_data[texNum - 30].maxTexSize_.y };
    maxTexSize = { texture_data[texNum - 30].maxTexSize_.x,
        texture_data[texNum - 30].maxTexSize_.y };
    MAX_HP = hp;
    HP = 0;
    scale = { scale_,scale_ };
    s = 0;
    color = { 1,1,1,1 };
    color_timer = 0;
    timer = 0;
    regenerate = regenerate_;
    break_build = false;
    break_timer = 0;
    texture_transition = stage->texture_transition;
    effct_anime = false;
    effectanimeNum = 0;
    currentEffectNum = 0;
    effectNum = 7;
    buildStatus = status;
    //effect_ = new Effect * [effectNum];
}

building::~building()
{
    GameLib::texture::release(texNum);
    texture_data[texNum - 30].load = false;
}

void building::update()
{
    texSize.y = -maxTexSize.y * (HP / MAX_HP);
    if (timer % 12 == 0 && break_build == false)
    {

        if (HP < MAX_HP)
        {
            HP += 1.0f;
        }
        else if (HP > MAX_HP)
        {
            HP = MAX_HP;
        }
    }
    else if (break_build)
    {
        if (texture_transition)
        {
            texSize.y = -maxTexSize.y;
            hp = HP;
            if (HP / MAX_HP > 0.98f) nowTexSize.x = maxTexSize.x * 2;
            else if (HP / MAX_HP > 0.7f) nowTexSize.x = maxTexSize.x * 3;
            else if (HP / MAX_HP > 0.6f) nowTexSize.x = maxTexSize.x * 4;
            else if (HP / MAX_HP > 0.4f) nowTexSize.x = maxTexSize.x * 5;
            else if (HP / MAX_HP > 0.2f) nowTexSize.x = maxTexSize.x * 6;
            else if (HP / MAX_HP > 0.0f) nowTexSize.x = maxTexSize.x * 7;
            else texSize.y = 0;
        }
        else
        {
            break_timer++;
            if (break_timer > 60 * 3)
            {
                this->break_build = false;
                break_timer = 0;
            }
        }

    }
    if (HP/MAX_HP>0.8f)
    {

        color.y -= sinf(color_timer) * 0.5f;
        color.z -= sinf(color_timer) * 0.5f;
        color.y < 0 ? color.y = 0 : color.y>1 ? color.y = 1 : color.y;
        color.z < 0 ? color.z = 0 : color.z>1 ? color.z = 1 : color.z;
        color_timer += DirectX::XMConvertToRadians(30);
    }
    else
    {
        color = { 1,1,1,1 };
    }


    if (effct_anime == true)
    {
        for (int i = 0; i < ItemNo::item_end; i++)
        {
            if (effectanimeNum != i) { continue; }
            switch (i)
            {
            case ItemNo::AXE:
                effect_[i]->effct_axe();
                break;
            case ItemNo::CHAINSAW:
                effect_[i]->effct_chainsaw();
                break;
            case ItemNo::FIRE:
                effect_[i]->effct_fire();
                break;
            case ItemNo::HAMMER:
                effect_[i]->effct_hammer();
                break;
            case ItemNo::DRILL:
                effect_[i]->effct_drill();
                break;
            case ItemNo::DYNAMITE:
                effect_[i]->effct_exprosion();
                break;
            case ItemNo::item_end:
                break;
            }

            if (effect_[i]->effectTimer >= 60)
            {
                effct_anime = false;
                effect_[i]->effectTimer = 0;
                if (effect_[i])
                {
                    delete effect_[i];
                }
            }
        }
    }
    if (addTimer > 1 && timer % 2 != 0)
        timer++;
    else
        timer += addTimer;
}

void building::draw()
{
    GameLib::texture::begin(texNum);
    GameLib::texture::draw(texNum, { position }, { scale }, { nowTexSize }, { texSize }, { -maxTexSize.x/2,0 }, 0,{color});
    GameLib::texture::end(texNum);

    for (int i = 0; i < ItemNo::item_end; i++)
    {
        if (effct_anime == true)
        {
            if (effectanimeNum != i) { continue; }
            switch (i)
            {
            case ItemNo::AXE:
                effect_[i]->effectNum = 53;
                effect_[i]->effect_texsize = { 32,32 };
                effect_[i]->effect_draw();
                break;
            case ItemNo::CHAINSAW:
                effect_[i]->effectNum = 54;
                effect_[i]->effect_texsize = { 64,64 };
                effect_[i]->effect_center = { 32,32 };
                effect_[i]->effect_scale = { 4,4 };
                effect_[i]->effect_draw();
                break;
            case ItemNo::FIRE:
                effect_[i]->effectNum = 51;
                effect_[i]->effect_center.y = 64;
                effect_[i]->effect_texsize = { 32,64 };
                effect_[i]->effect_draw();
                break;
            case ItemNo::HAMMER:
                effect_[i]->effectNum = 52;
                effect_[i]->effect_texsize = { 32,32 };
                effect_[i]->effect_draw();
                break;
            case ItemNo::DRILL:
                effect_[i]->effectNum = 54;
                effect_[i]->effect_texsize = { 64,64 };
                effect_[i]->effect_center = { 32,32 };
                effect_[i]->effect_scale = { 4,4 };
                effect_[i]->effect_draw();
                break;
            case ItemNo::DYNAMITE:
                effect_[i]->effectNum = 50;
                effect_[i]->effect_texsize = { 32,32 };
                effect_[i]->effect_draw();
                break;
            case ItemNo::item_end:
                break;

            }
        }
    }

    //GameLib::primitive::rect({ position.x - (maxTexSize.x * scale.x) / 2,position.y - (maxTexSize.y * scale.y)}, {maxTexSize.x * scale.x,maxTexSize.y * scale.y}, {0,0});
    GameLib::debug::setString("cost:%d", current_cost);

}

void building::hit(Item* item, int current_item)
{
    for (int i = 0; i < ItemNo::item_end; i++)
    {
        DirectX::XMFLOAT2 item_pos;
        item_pos = item->ItemUIManager()[i].position;
        DirectX::XMFLOAT2 build_pos;
        build_pos = { position.x - (maxTexSize.x * scale.x) / 2,position.y - (maxTexSize.y * scale.y) };
        DirectX::XMFLOAT2 build_width_height;
        build_width_height = { maxTexSize.x * scale.x,maxTexSize.y * scale.y };

        if (build_pos.x < item_pos.x &&
            build_pos.y < item_pos.y &&
            build_pos.x + build_width_height.x >item_pos.x &&
            build_pos.y + build_width_height.y >item_pos.y)
        {
            if (TRG_RELEASE(0) & GameLib::input::PAD_START)
            {
                switch (i)
                {
                case ItemNo::AXE:
                    item->Axe();
                    currentEffectNum = ItemNo::AXE;
                    itemStatus = Attribute::wood;
                    break;
                case ItemNo::CHAINSAW:
                    item->Chainsaw();
                    currentEffectNum = ItemNo::CHAINSAW;
                    itemStatus = Attribute::wood;
                    break;
                case ItemNo::FIRE:
                    item->Fire();
                    currentEffectNum = ItemNo::FIRE;
                    itemStatus = Attribute::wood;
                    break;
                case ItemNo::HAMMER:
                    item->Hammer();
                    currentEffectNum = ItemNo::HAMMER;
                    itemStatus = Attribute::stone;
                    break;
                case ItemNo::DRILL:
                    item->Drill();
                    currentEffectNum = ItemNo::DRILL;
                    itemStatus = Attribute::stone;
                    break;
                case ItemNo::DYNAMITE:
                    item->Dynamite();
                    currentEffectNum = ItemNo::DYNAMITE;
                    itemStatus = Attribute::stone;
                    break;
                case ItemNo::item_end:
                    break;
                }
                if (current_cost - item->getCost() >= 0)
                {
                    current_cost -= item->getCost();
                    HP -= item->getAttack();
                    item->setAttack(0);
                    //effect_ = new Effect * [effectNum];
                    /*for (int j = 0; j < currentEffectNum; j++)
                    {*/
                if (itemStatus != buildStatus)
                {
                    HP -= item->getAttack() / 2;
                }
                else
                {
                    HP -= item->getAttack();
                }
                item->setAttack(0);
                //effect_ = new Effect * [effectNum];
                /*for (int j = 0; j < currentEffectNum; j++)
                {*/
                    effect_[currentEffectNum] = new Effect(0, { 0,0 }, { 8,8 }, { 0,32 }, { 0,32 }, { 16,16 }, 50);
                    effect_[currentEffectNum]->effect_pos.x = item_pos.x;
                    effect_[currentEffectNum]->effect_pos.y = item_pos.y;
                    effct_anime = true;
                    effectanimeNum = i;
                    //}
                    //currentEffectNum++;
                    this->break_build = true;
                }
            }
            if (HP < 0) HP = 0;
        }
    }
}


void newEffect()
{
    effect_ = new Effect * [effectNum];
}