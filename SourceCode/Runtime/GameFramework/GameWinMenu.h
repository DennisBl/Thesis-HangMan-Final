#ifndef GAME_WIN_MENU_H
#define GAME_WIN_MENU_H

#include "GameCore.h"

class FWinMenu : public FCanvasMenu
{
public:
    FWinMenu();

    virtual void Render(FCanvasRenderer *InCanvasRenderer) override;
};

#endif