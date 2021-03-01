#include "GameLoseMenu.h"
#include "GameMenu.h"
#include "GameState.h"

#include <AssetFramework.h>

class FHomeButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState *MenuState = OwnerMenu->GetMenuState();
        MenuState->MenuCategory  = MC_MainMenu;
        MenuState->ReInitialize();
    }
};

class FNewGameButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState *MenuState = OwnerMenu->GetMenuState();
        MenuState->MenuCategory  = MC_PlayMenu;
        MenuState->ReInitialize();
    }
};

FLoseMenu::FLoseMenu()
{
    const FTexture2D* HomeTexture    = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/HOME.png");
    const FTexture2D* NewGameTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/GAME OVER/New Game-gr.png");

    FCanvasButton *Home = new FHomeButton();
    Home->Position = FIntRect(0, 650, 230, 720);
    Home->AlignX       = CX_Center;
    Home->AlignY       = CY_Top;
    Home->NormalBrush  = FContentBrush(HomeTexture, FColor32::White);
    Home->HoveredBrush = FContentBrush(HomeTexture, FColor32(200, 200, 200, 255));
    Home->ClickedBrush = FContentBrush(HomeTexture, FColor32::White);
    AddButton(Home);

    FCanvasButton *NewGame = new FNewGameButton();
    NewGame->Position = FIntRect(0, 650, 230, 720);
    NewGame->AlignX = CX_Center;
    NewGame->AlignY = CY_Top;
    NewGame->NormalBrush = FContentBrush(NewGameTexture, FColor32::White);
    NewGame->HoveredBrush = FContentBrush(NewGameTexture, FColor32(200, 200, 200, 255));
    NewGame->ClickedBrush = FContentBrush(NewGameTexture, FColor32::White);
    AddButton(NewGame);
}

void
FLoseMenu::Render(FCanvasRenderer* InCanvasRenderer)
{
    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);
    const FFontCache* FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/Greek.ttf");

    const FTexture2D* BackgroundTextureA = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/0 sea background-.png");
    const FTexture2D* BackgroundTextureB = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/1 deap.png");
    const FTexture2D* BackgroundTextureC = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/WATER TEXTURE.png");
    const FTexture2D* BackgroundTextureD = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/Hangman 4 Final-01.png");

    const FTexture2D* GameOverTexture  = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/GAME OVER/Game Over-gr.png");
    const FTexture2D* LayerTexture     = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/GAME OVER/LAYER.png");
    const FTexture2D* LineTexture      = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/GAME OVER/LINE.png");

    FGameState *GameState = (FGameState *)OwnerState;
    FString BenchScoreString(GameState->BenchScore);
    FString PeakStreakString(GameState->CurrentStreak);

    InCanvasRenderer->DrawSprite(BackgroundTextureA, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureB, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureC, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureD, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);

    InCanvasRenderer->DrawSprite(LayerTexture, 0, 0, 800, 800, FColor32::White, CX_Center, CY_Center);
    InCanvasRenderer->DrawSprite(GameOverTexture, 0, 175, 540, 75, FColor32::White, CX_Center, CY_Top);

    InCanvasRenderer->DrawText(FontCache, 1.2, "Skor", 0, 300, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawText(FontCache, 1.0, BenchScoreString, 0, 375, FColor32(200, 200, 200, 255), CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 425, 300, 5, FColor32::White, CX_Center, CY_Top);

    InCanvasRenderer->DrawText(FontCache, 1.2, "Seri", 0, 475, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawText(FontCache, 1.0, PeakStreakString, 0, 550, FColor32(200, 200, 200, 255), CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 600, 300, 5, FColor32::White, CX_Center, CY_Top);

    FCanvasMenu::Render(InCanvasRenderer);
}