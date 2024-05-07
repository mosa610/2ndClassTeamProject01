#include "effect.h"

Effect::Effect()
{
    effectTimer = 0;
    effectNum = 0;
    effect_pos = { 0,0 };
    effect_scale = { 8,8 };
    effect_texpos = { 0,32 };
    effect_texsize = { 0,32 };
    effect_center = { 16,16 };
}

Effect::Effect(int timer, VECTOR2 pos, VECTOR2 scale, VECTOR2 texpos, VECTOR2 texsize, VECTOR2 center,int num)
{
    effectTimer = timer;
    effect_pos = pos;
    effect_scale = scale;
    effect_texpos = texpos;
    effect_texsize = texsize;
    effect_center = center;
    effectNum = num;
}

Effect::~Effect()
{

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