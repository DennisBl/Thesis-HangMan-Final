#ifndef CANVAS_MENU_H
#define CANVAS_MENU_H

#include "CanvasRenderer.h"

class FCanvasButton;
class FCanvasMenuState;

struct FInputState;

class FCanvasMenu
{
public:
    FCanvasMenuState *OwnerState;
    TArray<FCanvasButton *> Buttons;

public:
    FCanvasMenu();
    virtual ~FCanvasMenu();

    void AddButton(FCanvasButton *InButton);
    void RemoveButton(FCanvasButton *InButton);

    virtual void ReInitialize();
    virtual void Update(FInputState *InputState);
    virtual void Render(FCanvasRenderer *InCanvasRenderer);

    FCanvasMenuState *GetMenuState();
};

#endif