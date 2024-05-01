#include "all.h"
#include "building.h"
#include "stage.h"
#include "Texture_data.h"
#include "effect.h"

int hp;
int effectNum;
extern Effect** effect;


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

building::building(Stage_script* stage, float position_x, int tex_num,float scale_,float hp, bool regenerate_, int build_num)
{
    GameLib::texture::load(texture_data[tex_num - 30].tex_num, texture_data[tex_num - 30].filename);
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
    effectNum = 1;
    effct_anime = false;
    building_number = build_num;
}

building::~building()
{
    GameLib::texture::release(texNum);
}

void building::update()
{
    texSize.y = -maxTexSize.y * (HP / MAX_HP);
    if (timer % 1 == 0 && break_build == false)
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
        effect[building_number]->effct_exprosion();
        //effect->effct_fire();

        if (effect[building_number]->effectTimer >= 60)
        {
            effct_anime = false;
            effect[building_number]->effectTimer = 0;
            if (effect)
            {
                delete effect[building_number];
            }
        }
    }
    timer++;
}

void building::draw()
{
    GameLib::texture::begin(texNum);
    GameLib::texture::draw(texNum, { position }, { scale }, { nowTexSize }, { texSize }, { -maxTexSize.x/2,0 }, 0,{color});
    GameLib::texture::end(texNum);

    if (effct_anime == true)
    {
       effect[building_number]->effect_draw();
    }

    //GameLib::primitive::rect({ position.x - (maxTexSize.x * scale.x) / 2,position.y - (maxTexSize.y * scale.y)}, {maxTexSize.x * scale.x,maxTexSize.y * scale.y}, {0,0});
    GameLib::debug::setString("hp%d", hp);

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

        if (build_pos.x<item_pos.x &&
            build_pos.y<item_pos.y &&
            build_pos.x + build_width_height.x >item_pos.x &&
            build_pos.y + build_width_height.y >item_pos.y)
        {
            if (TRG_RELEASE(0) & GameLib::input::PAD_START)
            {
                switch (i)
                {
                case ItemNo::AXE:
                    item->Axe();
                    break;
                case ItemNo::CHAINSAW:
                    item->Chainsaw();
                    break;
                case ItemNo::DRILL:
                    item->Drill();
                    break;
                case ItemNo::DYNAMITE:
                    item->Dynamite();
                    break;
                case ItemNo::FIRE:
                    item->Fire();
                    break;
                case ItemNo::HAMMER:
                    item->Hammer();
                    break;
                case ItemNo::item_end:
                    break;

                }
                HP -= item->getAttack();
                item->setAttack(0);
                if (effct_anime != true)
                {
                    effect[building_number] = new Effect;
                    effect[building_number]->effect_pos.x = item_pos.x;
                    effect[building_number]->effect_pos.y = item_pos.y;
                    effct_anime = true;
                }

                this->break_build = true;

            }
            if (HP < 0) HP = 0;
        }
    }
}
