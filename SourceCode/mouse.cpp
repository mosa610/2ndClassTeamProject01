#include "mouse.h"

Mouse Mouse::instance_;

void Mouse::setPosition()
{
    position = { (float)GameLib::input::getCursorPosX(),(float)GameLib::input::getCursorPosY() };
}

VECTOR2 Mouse::getPosition()
{
    return position;
}
