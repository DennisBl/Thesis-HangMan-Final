#ifndef GAME_MAIN_MENU_H
#define GAME_MAIN_MENU_H

#include "GameCore.h"

class FMainMenu : public FCanvasMenu
{
public:
    FMainMenu();

    virtual void Render(FCanvasRenderer *InCanvasRenderer) override;
};

#endif