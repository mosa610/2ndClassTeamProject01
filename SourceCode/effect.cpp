#include "effect.h"

Effect::Effect()
{
    effectTimer = 0;
    effect_pos = { 0,0 };
    effect_scale = { 8,8 };
    for (int i = 50; i < 51; i++)
    {
        GameLib::texture::load(50, effect_data[i - 50].filename);
    }
}

Effect::~Effect()
{
    GameLib::texture::release(50);
}

void Effect::effct_exprosion()
{
    effectTimer++;
    effect_texpos = { static_cast<float>(32 * (effectTimer / 12)),static_cast < float>(32) };
    if (effectTimer == 60)
    {
        return;
    }
}

void Effect::effct_fire()
{
    effectTimer++;
    effect_pos = { 0,0 };
    effect_texpos = { static_cast<float>(32 * (effectTimer / 12)),static_cast <float>(224) };
    if (effectTimer == 60)
    {
        return;
    }
}

void Effect::effect_draw()
{
    /*for (int i = 50; i < 51; i++)
    {*/
        GameLib::texture::begin(50);
        GameLib::texture::draw(50, { effect_pos }, { effect_scale }, { effect_texpos }, { 32, 32 }, { 16,16 });
        GameLib::texture::end(50);
    //}
}