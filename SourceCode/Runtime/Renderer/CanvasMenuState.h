#ifndef CANVAS_MENU_STATE_H
#define CANVAS_MENU_STATE_H

#include "CanvasRenderer.h"

class FCanvasButton;
class FCanvasMenu;

struct FInputState
{
    int32 CursorX;
    int32 CursorY;

    uint16 bIsClicked;
    uint16 bIsReleased;
};

class FCanvasMenuState
{
public:
    int32 MenuCategory;
    TArray<FCanvasMenu *> Menus;

public:
    virtual ~FCanvasMenuState();

    void AddMenu(FCanvasMenu *InMenu);
    void RemoveMenu(FCanvasMenu *InMenu);

    virtual void ReInitialize();
    virtual void UpdateAndRender(FCanvasRenderer *InCanvasRenderer, FInputState *InputState);

    FORCEINLINE FCanvasMenu *GetMenuById(int32 Id)
    {
        return Menus[Id];
    }
};

#endif