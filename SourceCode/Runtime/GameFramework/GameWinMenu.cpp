#include "GameWinMenu.h"
#include "GamePlayMenu.h"
#include "GameMenu.h"
#include "GameState.h"

#include <AssetFramework.h>

class FHomeButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState *MenuState = OwnerMenu->GetMenuState();
        MenuState->MenuCategory = MC_MainMenu;
        MenuState->ReInitialize();
    }
};

class FContinueButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState *MenuState = OwnerMenu->GetMenuState();
        MenuState->MenuCategory = MC_PlayMenu;

        FPlayMenu *PlayMenu = (FPlayMenu *)MenuState->GetMenuById(MC_PlayMenu);
        PlayMenu->bIsInPlay = true;
    }
};

FWinMenu::FWinMenu()
{
    const FTexture2D* HomeTexture     = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/HOME.png");
    const FTexture2D* ContinueTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/Continue-gr.png");

    FCanvasButton* Continue = new FContinueButton();
    Continue->Position     = FIntRect(0, 650, 230, 740);
    Continue->AlignX       = CX_Center;
    Continue->AlignY       = CY_Top;
    Continue->NormalBrush  = FContentBrush(ContinueTexture, FColor32::White);
    Continue->HoveredBrush = FContentBrush(ContinueTexture, FColor32(200, 200, 200, 255));
    Continue->ClickedBrush = FContentBrush(ContinueTexture, FColor32::White);
    AddButton(Continue);

    FHomeButton * Home = new FHomeButton();
    Home->Position     = FIntRect(0, 755, 70, 825);
    Home->AlignX       = CX_Center;
    Home->AlignY       = CY_Top;
    Home->NormalBrush  = FContentBrush(HomeTexture, FColor32::White);
    Home->HoveredBrush = FContentBrush(HomeTexture, FColor32(200, 200, 200, 255));
    Home->ClickedBrush = FContentBrush(HomeTexture, FColor32::White);
    AddButton(Home);
}

void
FWinMenu::Render(FCanvasRenderer *InCanvasRenderer)
{
    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

    //const FFontCache *FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/ComicSansMSBold.ttf");
    const FFontCache* FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/Greek.ttf");

    const FTexture2D *BackgroundTextureA = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/0 sea background-.png");
    const FTexture2D *BackgroundTextureB = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/1 deap.png");
    const FTexture2D *BackgroundTextureC = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/WATER TEXTURE.png");
    const FTexture2D *BackgroundTextureD = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/Hangman 4 Final-01.png");

    const FTexture2D *CorrectTexture   = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/Correct-gr.png");
    const FTexture2D *LayerTexture     = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/LAYER.png");
    const FTexture2D *LineTexture      = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/LINE.png");

    FGameState *GameState = (FGameState *)OwnerState;
    FString BenchScoreString(GameState->BenchScore);
    FString PeakStreakString(GameState->CurrentStreak);

    InCanvasRenderer->DrawSprite(BackgroundTextureA, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureB, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureC, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureD, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);

    InCanvasRenderer->DrawSprite(LayerTexture, 0, 0, 800, 800, FColor32::White, CX_Center, CY_Center);
    InCanvasRenderer->DrawSprite(CorrectTexture, 0, 175, 300, 75, FColor32::White, CX_Center, CY_Top);

    InCanvasRenderer->DrawText(FontCache, 1.2, "Skor", 0, 300, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawText(FontCache, 1.0, BenchScoreString, 0, 375, FColor32(200, 200, 200, 255), CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 425, 300, 5, FColor32::White, CX_Center, CY_Top);

    InCanvasRenderer->DrawText(FontCache, 1.2, "Seri", 0, 475, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawText(FontCache, 1.0, PeakStreakString, 0, 550, FColor32(200, 200, 200, 255), CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 600, 300, 5, FColor32::White, CX_Center, CY_Top);

    FCanvasMenu::Render(InCanvasRenderer);
}