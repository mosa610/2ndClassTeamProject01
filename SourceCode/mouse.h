#pragma once

#include "all.h"

class Mouse
{
private:
    static Mouse instance_;
public:
    static Mouse* instance() { return &instance_; }
    void setPosition();
    VECTOR2 getPosition();
private:
    Mouse() {}
    Mouse(const Mouse&) = delete;
private:
    VECTOR2 position = {};
};
