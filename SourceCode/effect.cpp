#include "effect.h"

Effect::Effect()
{
    effectTimer = 0;
    effect_pos = { 0,0 };
    effect_scale = { 8,8 };
    effectNum = 0;
    for (int i = 50; i < 55; i++)
    {
        GameLib::texture::load(i, effect_data[i - 50].filename);
    }
}

Effect::~Effect()
{
    GameLib::texture::release(50);
    GameLib::texture::release(51);
    GameLib::texture::release(52);
    GameLib::texture::release(53);
    GameLib::texture::release(54);
}

void Effect::effct_exprosion()
{
    effectTimer++;
    effect_texpos = { static_cast<float>(32 * (effectTimer / 12)),static_cast <float>(32) };
    if (effectTimer == 60)
    {
        return;
    }
}

void Effect::effct_fire()
{
    effectTimer++;
    effect_texpos = { static_cast<float>(32 * (effectTimer / 5)),static_cast <float>(0) };
    if (effectTimer == 60)
    {
        return;
    }
}

void Effect::effct_hammer()
{
    effectTimer++;
    effect_texpos = { static_cast<float>(32 * (effectTimer / 20)),static_cast <float>(0) };
    if (effectTimer == 60)
    {
        return;
    }
}

void Effect::effct_axe()
{
    effectTimer++;
    effect_texpos = { static_cast<float>(32 * (effectTimer / 12)),static_cast <float>(0) };
    if (effectTimer == 60)
    {
        return;
    }
}

void Effect::effct_chainsaw()
{
    effectTimer++;
    effect_texpos = { static_cast<float>(64 * (effectTimer / 4)),static_cast <float>(0) };
    if (effectTimer == 60)
    {
        return;
    }
}

void Effect::effct_drill()
{
    effectTimer++;
    effect_texpos = { static_cast<float>(64 * (effectTimer / 4)),static_cast <float>(64) };
    if (effectTimer == 60)
    {
        return;
    }
}
void Effect::effect_draw()
{    
    GameLib::texture::begin(effectNum);
    GameLib::texture::draw(effectNum, { effect_pos }, { effect_scale }, { effect_texpos }, { effect_texsize }, { effect_center });
    GameLib::texture::end(effectNum);
}