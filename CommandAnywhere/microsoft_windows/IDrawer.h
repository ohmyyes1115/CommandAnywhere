#pragma once
#include "Canvas.h"

class IDrawer {
public:
    virtual ~IDrawer() = default;
    virtual void draw(Canvas& canvas) = 0;
};
