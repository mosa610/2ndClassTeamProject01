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
float distHP;
float hage_pos_x = 0;
float hage_speed = 3.0f;
float hage_scale_x = 2;
extern float hage_texpos_x;
int plusHP;
extern int weather;
bool doEffect;

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
    texture_transition = stage[stageNumber].texture_transition;
    effct_anime = false;
    effectanimeNum = 0;
    currentEffectNum = 0;
    effectNum = 7;
    buildStatus = status;
    GameLib::texture::load(ui[4].tex_num, ui[4].filename);
    //effect_ = new Effect * [effectNum];
}

building::~building()
{
    if (texture_data[texNum - 30].load == true)
    {
        GameLib::texture::release(texNum);
        texture_data[texNum - 30].load = false;
    }
    GameLib::texture::release(5);
}

void building::update()
{
    hageHit = false;
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
                effect_[ItemNo::AXE]->effct_axe();
                break;
            case ItemNo::CHAINSAW:
                if (weather == Weather::thunder)
                {
                    break;
                }
                else
                {
                    effect_[i]->effct_chainsaw();
                    break;
                }
            case ItemNo::FIRE:
                if (weather == Weather::rain)
                {
                    break;
                }
                else
                {
                    effect_[i]->effct_fire();
                    break;
                }
            case ItemNo::HAMMER:
                effect_[ItemNo::HAMMER]->effct_hammer();
                break;
            case ItemNo::DRILL:
                if (weather == Weather::thunder)
                {
                    break;
                }
                else
                {
                    effect_[i]->effct_drill();
                    break;
                }
            case ItemNo::DYNAMITE:
                if (weather == Weather::rain)
                {
                    break;
                }
                else
                {
                    effect_[i]->effct_exprosion();
                    break;
                }
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
    GameLib::texture::draw(texNum, { position }, { scale.x,scale.y }, { nowTexSize }, { texSize }, { -maxTexSize.x/2,0 }, 0,{color});
    GameLib::texture::end(texNum);
    for (int i = 0; i < ItemNo::item_end; i++)
    {
        if (effct_anime == true)
        {
            if (effectanimeNum != i) { continue; }
            switch (i)
            {
            case ItemNo::AXE:
                effect_[ItemNo::AXE]->effectNum = 53;
                effect_[ItemNo::AXE]->effect_texsize = { 32,32 };
                effect_[ItemNo::AXE]->effect_draw();
                break;
            case ItemNo::CHAINSAW:
                if (weather == Weather::thunder)
                {
                    break;
                }
                else
                {
                    effect_[i]->effectNum = 54;
                    effect_[i]->effect_texsize = { 64,64 };
                    effect_[i]->effect_center = { 32,32 };
                    effect_[i]->effect_scale = { 4,4 };
                    effect_[i]->effect_draw();
                    break;
                }
            case ItemNo::FIRE:
                if (weather == Weather::rain)
                {
                    break;
                }
                else
                {
                    effect_[i]->effectNum = 51;
                    effect_[i]->effect_center.y = 64;
                    effect_[i]->effect_texsize = { 32,64 };
                    effect_[i]->effect_draw();
                    break;
                }
            case ItemNo::HAMMER:
                effect_[ItemNo::HAMMER]->effectNum = 52;
                effect_[ItemNo::HAMMER]->effect_texsize = { 32,32 };
                effect_[ItemNo::HAMMER]->effect_draw();
                break;
            case ItemNo::DRILL:
                if (weather == Weather::thunder)
                {
                    break;
                }
                else
                {
                    effect_[i]->effectNum = 54;
                    effect_[i]->effect_texsize = { 64,64 };
                    effect_[i]->effect_center = { 32,32 };
                    effect_[i]->effect_scale = { 4,4 };
                    effect_[i]->effect_draw();
                    break;
                }
            case ItemNo::DYNAMITE:
                if (weather == Weather::rain)
                {
                    break;
                }
                else
                {
                    effect_[i]->effectNum = 50;
                    effect_[i]->effect_texsize = { 32,32 };
                    effect_[i]->effect_draw();
                    break;
                }
            case ItemNo::item_end:
                break;

            }
        }
    }


    //GameLib::primitive::rect({ position.x - (maxTexSize.x * scale.x) / 2,position.y - (maxTexSize.y * scale.y)}, {maxTexSize.x * scale.x,maxTexSize.y * scale.y}, {0,0});
   
    GameLib::debug::setString("cost:%d", current_cost);
    //GameLib::primitive::circle({ hage_pos }, 200, { 1,1 }, 0, { 1,0,0,0.5f });
    /*GameLib::texture::begin(ui[4].tex_num);
    GameLib::texture::draw(ui[4].tex_num, { hage_pos_x,690 }, { -hage_scale_x,4 }, { 0,0 }, { 32,32 }, { 16,16 }, 0, { 1,1,1,1 });
    GameLib::texture::end(ui[4].tex_num);*/
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
                doEffect = true;
                switch (i)
                {
                case ItemNo::AXE:
                    item->Axe();
                    currentEffectNum = ItemNo::AXE;
                    itemStatus = Attribute::wood;
                    break;
                case ItemNo::CHAINSAW:
                    if (weather == Weather::thunder)
                    {
                        doEffect = false;
                        break;
                    }
                    else
                    {
                        item->Chainsaw();
                        currentEffectNum = ItemNo::CHAINSAW;
                        itemStatus = Attribute::wood;
                        break;
                    }
                case ItemNo::FIRE:
                    if (weather == Weather::rain)
                    {
                        doEffect = false;
                        break;
                    }
                    else
                    {
                        item->Fire();
                        currentEffectNum = ItemNo::FIRE;
                        itemStatus = Attribute::wood;
                        break;
                    }
                case ItemNo::HAMMER:
                    item->Hammer();
                    currentEffectNum = ItemNo::HAMMER;
                    itemStatus = Attribute::stone;
                    break;
                case ItemNo::DRILL:
                    if (weather == Weather::thunder)
                    {
                        doEffect = false;
                        break;
                    }
                    else
                    {
                        item->Drill();
                        currentEffectNum = ItemNo::DRILL;
                        itemStatus = Attribute::stone;
                        break;
                    }
                case ItemNo::DYNAMITE:
                    if (weather == Weather::rain)
                    {
                        doEffect = false;
                        break;
                    }
                    else
                    {
                        item->Dynamite();
                        currentEffectNum = ItemNo::DYNAMITE;
                        itemStatus = Attribute::stone;
                        break;
                    }
                case ItemNo::item_end:
                    break;
                }
                if (current_cost - item->getCost() >= 0)
                {
                    current_cost -= item->getCost();

                    distHP = HP;
                    if (itemStatus != buildStatus)
                    {
                        HP -= item->getAttack() / 2;
                    }
                    else
                    {
                        HP -= item->getAttack();
                    }
                    item->setAttack(0);

                    plusHP = static_cast<int>(((distHP - HP) * (distHP / MAX_HP)) / 2);


                    if (doEffect)
                    {
                        effect_[currentEffectNum] = new Effect(0, { 0,0 }, { 8,8 }, { 0,32 }, { 0,32 }, { 16,16 }, 50);
                        hageHit = true;

                        effect_[currentEffectNum]->effect_pos.x = item_pos.x;
                        effect_[currentEffectNum]->effect_pos.y = item_pos.y;
                        effct_anime = true;
                        effectanimeNum = i;
                    }

                    //}
                    //currentEffectNum++;
                    this->break_build = true;
                }
            }
            if (HP < 0) HP = 0;
        }
    }
}

void building::hageVSBuild(float hagepos, float radius)
{
    DirectX::XMFLOAT2 build_pos;
    build_pos = { position.x ,position.y };
    if (build_pos.x > hagepos - radius &&
        build_pos.x < hagepos + radius)
    {
        if(hageHit)
        plusHP = -50;
    }
}

void hage()
{
    if (hage_pos_x > 1904)
    {
        hage_speed *= -1.0f;
        hage_scale_x *= -1.0f;
    }
    if (hage_pos_x < 0)
    {
        hage_speed *= -1.0f;
        hage_scale_x *= -1.0f;
    }

    hage_pos_x += hage_speed * addTimer;
}


void newEffect(int effectNum)
{
    effect_ = new Effect * [effectNum];

}