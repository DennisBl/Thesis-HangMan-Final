#include "CanvasMenuState.h"
#include "CanvasMenu.h"
#include "CanvasButton.h"

FCanvasMenuState::~FCanvasMenuState()
{
    for (FCanvasMenu *Menu : Menus)
    {
        delete Menu;
    }
}

void
FCanvasMenuState::AddMenu(FCanvasMenu *InMenu)
{
    Menus.Add(InMenu);
    InMenu->OwnerState = this;
}

void
FCanvasMenuState::RemoveMenu(FCanvasMenu *InMenu)
{
    Menus.Remove(InMenu);
    InMenu->OwnerState = 0;
}

void
FCanvasMenuState::ReInitialize()
{
    for (FCanvasMenu *Menu : Menus)
    {
        Menu->ReInitialize();
    }
}

void
FCanvasMenuState::UpdateAndRender(FCanvasRenderer *InCanvasRenderer, FInputState *InputState)
{
    FCanvasMenu *CurrentMenu = Menus[MenuCategory];
    CurrentMenu->Update(InputState);
    CurrentMenu->Render(InCanvasRenderer);
}

FCanvasMenu *
FCanvasButton::GetMenu()
{
    return OwnerMenu;
}

FCanvasMenuState *
FCanvasButton::GetMenuState()
{
    return OwnerMenu->OwnerState;
}

FCanvasMenuState *
FCanvasMenu::GetMenuState()
{
    return OwnerState;
}