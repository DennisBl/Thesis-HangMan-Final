#include "GameMainMenu.h"

#include <AssetFramework.h>

class FPlayButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState *MenuCategory = GetMenuState();
        MenuCategory->MenuCategory = MC_PlayMenu;

        FCanvasMenuState *MenuState = OwnerMenu->GetMenuState();
        FCanvasMenu *CanvasMenu = MenuState->GetMenuById(MC_PlayMenu);
        CanvasMenu->ReInitialize();
    }
};

class FRecordsButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState *MenuCategory = GetMenuState();
        MenuCategory->MenuCategory = MC_RecordsMenu;
        MenuCategory->ReInitialize();

    }
};

class FQuitButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FApplication::Get()->RequestClose();
    }
};

FMainMenu::FMainMenu()
{
    //English
    //const FTexture2D *PlayTexture    = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/Asset 25xhdpi.png");
   // const FTexture2D *RecordsTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/2 RECORDS/Asset 28xhdpi.png");
   // const FTexture2D *QuitTexture    = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/3 QUIT/Asset 30xhdpi.png");

    const FTexture2D* PlayTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/Asset 27xhdpi.png");
    const FTexture2D* RecordsTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/2 RECORDS/Asset 29xhdpi.png");
    const FTexture2D* QuitTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/3 QUIT/Asset 31xhdpi.png");

    FCanvasButton *PlayButton = new FPlayButton();
    PlayButton->Position     = FIntRect(0, 200, 400, 320);
    PlayButton->AlignX       = CX_Center;
    PlayButton->AlignY       = CY_Top;
    PlayButton->NormalBrush  = FContentBrush(PlayTexture, FColor32::White);
    PlayButton->HoveredBrush = FContentBrush(PlayTexture, FColor32(200, 200, 200, 255));
    PlayButton->ClickedBrush = FContentBrush(PlayTexture, FColor32::White);
    AddButton(PlayButton);

    FCanvasButton *RecordsButton = new FRecordsButton();
    RecordsButton->Position     = FIntRect(0, 400, 400, 520);
    RecordsButton->AlignX       = CX_Center;
    RecordsButton->AlignY       = CY_Top;
    RecordsButton->NormalBrush  = FContentBrush(RecordsTexture, FColor32::White);
    RecordsButton->HoveredBrush = FContentBrush(RecordsTexture, FColor32(200, 200, 200, 255));
    RecordsButton->ClickedBrush = FContentBrush(RecordsTexture, FColor32::White);
    AddButton(RecordsButton);

    FCanvasButton *QuitButton = new FQuitButton();
    QuitButton->Position      = FIntRect(0, 600, 400, 720);
    QuitButton->AlignX        = CX_Center;
    QuitButton->AlignY        = CY_Top;
    QuitButton->NormalBrush   = FContentBrush(QuitTexture, FColor32::White);
    QuitButton->HoveredBrush  = FContentBrush(QuitTexture, FColor32(200, 200, 200, 255));
    QuitButton->ClickedBrush  = FContentBrush(QuitTexture, FColor32::White);
    AddButton(QuitButton);
}

void
FMainMenu::Render(FCanvasRenderer *InCanvasRenderer)
{
    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

    const FTexture2D *BackgroundTextureA = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/0 sea background-.png");
    const FTexture2D *BackgroundTextureB = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/1 deap.png");
    const FTexture2D *BackgroundTextureC = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/WATER TEXTURE.png");
    const FTexture2D *BackgroundTextureD = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/Hangman 4 Final-01.png");

    InCanvasRenderer->DrawSprite(BackgroundTextureA, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureB, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureC, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureD, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);

    FCanvasMenu::Render(InCanvasRenderer);
}