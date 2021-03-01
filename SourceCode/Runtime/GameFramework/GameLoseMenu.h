#ifndef GAME_LOSE_MENU_H
#define GAME_LOSE_MENU_H

#include "GameCore.h"

class FLoseMenu : public FCanvasMenu
{
public:
    FLoseMenu();

    virtual void Render(FCanvasRenderer *InCanvasRenderer) override;
};

#endif