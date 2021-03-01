#include "CanvasMenu.h"
#include "CanvasButton.h"
#include "CanvasMenuState.h"

FCanvasMenu::FCanvasMenu()
    : OwnerState(0)
{ }

FCanvasMenu::~FCanvasMenu()
{
    for (FCanvasButton *Button : Buttons)
    {
        delete Button;
    }
}

void 
FCanvasMenu::AddButton(FCanvasButton *InButton)
{
    Buttons.Add(InButton);
    InButton->OwnerMenu = this;
}

void 
FCanvasMenu::RemoveButton(FCanvasButton *InButton)
{
    Buttons.Remove(InButton);
    InButton->OwnerMenu = 0;
}

void
FCanvasMenu::ReInitialize()
{

}

void
FCanvasMenu::Update(FInputState *InputState)
{
    for (FCanvasButton *Button : Buttons)
    {
        if (Button->ButtonState != BS_Disabled)
        {
            FIntRect AlignedRect;
            FCanvasRenderer::CalcAlignedPosition(Button->Position, &AlignedRect, Button->AlignX, Button->AlignY);

            if (InputState->CursorX >= AlignedRect.GetOriginX() &&
                InputState->CursorY >= AlignedRect.GetOriginY() &&
                InputState->CursorX <= AlignedRect.GetOriginX() + AlignedRect.GetSizeX() &&
                InputState->CursorY <= AlignedRect.GetOriginY() + AlignedRect.GetSizeY())
            {
                if (InputState->bIsClicked)
                {
                    Button->OnClick();
                }
                else if (InputState->bIsReleased)
                {
                    Button->OnRelease();
                }
                else
                {
                    Button->OnHover();
                }
            }
        }
    }
}

void 
FCanvasMenu::Render(FCanvasRenderer *InCanvasRenderer)
{
    for (FCanvasButton *Button : Buttons)
    {
        Button->Render(InCanvasRenderer);
    }
}