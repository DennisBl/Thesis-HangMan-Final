#include "GameMenu.h"
#include "GameState.h"

#include <AssetFramework.h>
#include "GameCharCodeMap.h"

static const int32 BenchScoreCoef = 10;
static const int32 DrawHintMsMax  = 3000;

class FHomeButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState* MenuState = OwnerMenu->GetMenuState();
        MenuState->MenuCategory = MC_MainMenu;
    }
};

class FGameMenuLetterButton : public FCanvasButton
{
public:
    TCHAR Letter;

public:
    virtual void OnRelease() override
    {
        FGameMenu *GameMenu = (FGameMenu *)OwnerMenu;
        if (GameMenu->UpdateState(Letter))
        {
            ButtonState = BS_Disabled;
            DisabledBrush.ColorAndOpacity = FColor32(0, 255, 0, 255);
        }
        else
        {
            ButtonState = BS_Disabled;
            DisabledBrush.ColorAndOpacity = FColor32(255, 0, 0, 255);
        }
    }
};

class FGameMenuHintButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FGameMenu *GameMenu = (FGameMenu *)OwnerMenu;
        GameMenu->bShowHint = true;
        GameMenu->DrawHintMs = DrawHintMsMax;
    }
};

FGameMenu::FGameMenu()
{
    const FTexture2D *GameHintButton = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/HINT/Asset 114xhdpi.png");
    const TCHAR Letters[24] = { 'A' , 'B', 'G', 'D', 'E', 'Z', 'H', 'U', 'I', 'K', 'L', 'M', 'N', 'J', 'O', 'P', 'R', 'S', 'T', 'Y', 'F', 'X', 'C', 'V' };
    for (int32 Index = 0; Index < 10; ++Index)
    {
        //FString Directory = "Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/ENG ALPHABET/" + FString(Letters[Index]) + ".png";
        FString Directory = "Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/GREEK ALPHABET/" + FString(Letters[Index]) + ".png";
        const FTexture2D *Texture = FAssetManager::Get()->FindOrCreateTexture2D(Directory);
       
        FGameMenuLetterButton *LetterButton = new FGameMenuLetterButton();
        LetterButton->Letter = Letters[Index];
        LetterButton->Position    = FIntRect(920 + Index * 80, 350, 970 + Index * 80, 430);
        LetterButton->AlignX      = CX_Left;
        LetterButton->AlignY      = CY_Top;
        LetterButton->DisabledBrush = FContentBrush(Texture, FColor32::White);
        LetterButton->NormalBrush   = FContentBrush(Texture, FColor32::White);
        LetterButton->HoveredBrush  = FContentBrush(Texture, FColor32::White);
        LetterButton->ClickedBrush  = FContentBrush(Texture, FColor32::White);
        AddButton(LetterButton);
    }
    for (int32 Index = 0; Index < 10; ++Index)
    {
        FString Directory = "Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/GREEK ALPHABET/" + FString(Letters[10 + Index]) + ".png";
        const FTexture2D *Texture = FAssetManager::Get()->FindOrCreateTexture2D(Directory);

        FGameMenuLetterButton *LetterButton = new FGameMenuLetterButton();
        LetterButton->Letter = Letters[10 + Index];
        LetterButton->Position = FIntRect(880 + Index * 80, 450, 930 + Index * 80, 530);
        LetterButton->AlignX = CX_Left;
        LetterButton->AlignY = CY_Top;
        LetterButton->DisabledBrush = FContentBrush(Texture, FColor32::White);
        LetterButton->NormalBrush   = FContentBrush(Texture, FColor32::White);
        LetterButton->HoveredBrush  = FContentBrush(Texture, FColor32::White);
        LetterButton->ClickedBrush  = FContentBrush(Texture, FColor32::White);
        AddButton(LetterButton);
    }
    for (int32 Index = 0; Index < 4; ++Index)
    {
        FString Directory = "Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/GREEK ALPHABET/" + FString(Letters[20 + Index]) + ".png";
        const FTexture2D *Texture = FAssetManager::Get()->FindOrCreateTexture2D(Directory);

        FGameMenuLetterButton *LetterButton = new FGameMenuLetterButton();
        LetterButton->Letter = Letters[20 + Index];
        LetterButton->Position = FIntRect(1100 + Index * 80, 550, 1150 + Index * 80, 630);
        LetterButton->AlignX = CX_Left;
        LetterButton->AlignY = CY_Top;
        LetterButton->DisabledBrush = FContentBrush(Texture, FColor32::White);
        LetterButton->NormalBrush   = FContentBrush(Texture, FColor32::White);
        LetterButton->HoveredBrush  = FContentBrush(Texture, FColor32::White);
        LetterButton->ClickedBrush  = FContentBrush(Texture, FColor32::White);
        AddButton(LetterButton);
    }

    FGameMenuHintButton *HintButton = new FGameMenuHintButton();
    HintButton->Position = FIntRect(-25, 50, 50, 125);
    HintButton->AlignX = CX_Right;
    HintButton->AlignY = CY_Center;
    HintButton->DisabledBrush = FContentBrush(GameHintButton, FColor32::White);
    HintButton->NormalBrush   = FContentBrush(GameHintButton, FColor32::White);
    HintButton->HoveredBrush  = FContentBrush(GameHintButton, FColor32(200, 200, 200, 255));
    HintButton->ClickedBrush  = FContentBrush(GameHintButton, FColor32::White);
    AddButton(HintButton);

    const FTexture2D* HomeTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/HOME.png");
    FHomeButton* HomeButton = new FHomeButton();
    HomeButton->Position = FIntRect(25, 25, 95, 95);
    HomeButton->AlignX = CX_Left;
    HomeButton->AlignY = CY_Top;
    HomeButton->NormalBrush = FContentBrush(HomeTexture, FColor32::White);
    HomeButton->HoveredBrush = FContentBrush(HomeTexture, FColor32(200, 200, 200, 255));
    HomeButton->ClickedBrush = FContentBrush(HomeTexture, FColor32::White);
    AddButton(HomeButton);
}

void
FGameMenu::InitializeState()
{
    FMemory::Zero(&bIsLetterFound, sizeof(bIsLetterFound));
    RoundCounter = 1;
    GameWord.Empty();

    for (FCanvasButton *Button : Buttons)
    {
        Button->ButtonState = BS_Normal;
    }
}

bool
FGameMenu::UpdateState(const TCHAR &InLetter)
{
    RoundCounter++;

    uint32 LettersFound = 0;

    for (uint32 Index = 0; Index < GameWord.GetLength(); ++Index)
    {
        const TCHAR& Letter = GameWord[Index];
        if (Letter == ' ')
        {
            bIsLetterFound[Index] = true;
            break;
        }
    }
    for (uint32 Index = 0; Index < GameWord.GetLength(); ++Index)
    {
        const TCHAR &Letter = GameWord[Index];


        if (Letter == InLetter)
        {
            FGameState* GameState  = (FGameState*)OwnerState;
            GameState->BenchScore += BenchScoreCoef;

            LettersFound++;
            bIsLetterFound[Index] = true;
        }
    }

    if (LettersFound != 0)
    {
        bool bIsWon = true;
        for (uint32 Index = 0; Index < GameWord.GetLength(); ++Index)
        {
            if (bIsLetterFound[Index] == false)
            {
                bIsWon = false;
                break;
            }
        }

        if (bIsWon)
        {
            FGameState *GameState = (FGameState *)OwnerState;
            GameState->BenchScore += (26 - RoundCounter) + 100;
            GameState->CurrentStreak++;

            FPlatformFileIni RecordsFile("../Records.ini");
            RecordsFile.BeginReadback(GameState->PlayerName);
            int32 BenchScore = RecordsFile.ReadInteger("BenchScore");
            int32 PeakStreak = RecordsFile.ReadInteger("PeakStreak");
            RecordsFile.EndReadback();

            RecordsFile.BeginWriteStream(GameState->PlayerName);
            if (GameState->BenchScore > BenchScore)
            {
                RecordsFile.WriteInteger("BenchScore", GameState->BenchScore);
            }
            if (GameState->CurrentStreak > PeakStreak)
            {
                RecordsFile.WriteInteger("PeakStreak", GameState->CurrentStreak);
            }
            RecordsFile.EndWriteStream();

            OwnerState->MenuCategory = MC_WinMenu;
        }

        return true;
    }
    else
    {
        FGameState *GameState = (FGameState *)OwnerState;
        GameState->BenchScore -= BenchScoreCoef;
        GameState->BenchScore = FMath::Max(0, GameState->BenchScore);

        LifeCount--;
        if (LifeCount == 0)
        {
            FPlatformFileIni RecordsFile("../Records.ini");
            RecordsFile.BeginReadback(GameState->PlayerName);
            int32 BenchScore = RecordsFile.ReadInteger("BenchScore");
            int32 PeakStreak = RecordsFile.ReadInteger("PeakStreak");
            RecordsFile.EndReadback();

            RecordsFile.BeginWriteStream(GameState->PlayerName);
            if (GameState->BenchScore > BenchScore)
            {
                RecordsFile.WriteInteger("BenchScore", GameState->BenchScore);
            }
            if (GameState->CurrentStreak > PeakStreak)
            {
                RecordsFile.WriteInteger("PeakStreak", GameState->CurrentStreak);
            }
            RecordsFile.EndWriteStream();

            OwnerState->MenuCategory = MC_LoseMenu;
        }

        return false;
    }
}

void
FGameMenu::Render(FCanvasRenderer *InCanvasRenderer)
{
    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

    const FFontCache *FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/Greek.ttf");


    const FTexture2D *HeartTexture               = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/LIVES/Asset 116xhdpi.png");
    const FTexture2D *GameBackgroundTexture      = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/0 Hangman 2  Background.jpg");
    const FTexture2D *GameScoreTexture           = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/HIGH SCORE/Asset 119xhdpi.png");
    const FTexture2D *GameEmptyLetterTexture     = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/ENG ALPHABET/SPACE.png");

    const FTexture2D *GameHeadTexture            = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/0 HEAD/HEAD VISIBLE.png");
    const FTexture2D *GameHeadShadowTexture      = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/0 HEAD/HEAD SHADOW.png");
    const FTexture2D *GameHandLeftTexture        = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/1 HAND/LEFT HAND.png");
    const FTexture2D *GameHandLeftShadowTexture  = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/1 HAND/LEFT HAND SHADOW.png");
    const FTexture2D *GameHandRightTexture       = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/1 HAND/RIGHT-HAND.png");
    const FTexture2D *GameHandRightShadowTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/1 HAND/RIGHT HAND-SHADOW.png");
    const FTexture2D *GameMainBodyTexture        = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/2 BODY/BODY VISIBLE.png");
    const FTexture2D *GameMainBodyShadowTexture  = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/2 BODY/BODY SHADOW.png");
    const FTexture2D *GameLegLeftTexture         = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/3 LEGS/LEFT LEG.png");
    const FTexture2D *GameLegLeftShadowTexture   = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/3 LEGS/LEFT LEG SHADOW.png");
    const FTexture2D *GameLegRightTexture        = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/3 LEGS/RIGHT LEG.png");
    const FTexture2D *GameLegRightShadowTexture  = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/3 LEGS/RIGHT LEG SHADOW.png");
    const FTexture2D *GameSunglassesTexture      = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Girl/4 SUNGLASSES/SUNGLASSES.png");
    
    const FTexture2D *GameSeaWaveTextureLayerA   = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Seawave/SEAWAVE 2/Wave-1.png");
    const FTexture2D *GameSeaWaveTextureLayerB   = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Seawave/SEAWAVE 2/Wave-2.png");
    const FTexture2D *GameSeaWaveTextureLayerC   = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Seawave/SEAWAVE 2/Water-1.png");
    const FTexture2D *GameSeaWaveTextureLayerD   = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Seawave/SEAWAVE 2/Water-2.png");

    FGameState *GameMenu = (FGameState *)OwnerState;

    const FString ScoreCounterString = FString(GameMenu->BenchScore);
    const FString RoundCounterString = FString(RoundCounter);

    InCanvasRenderer->DrawSprite(GameBackgroundTexture, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(GameSeaWaveTextureLayerA, 0, 0, ResolutionSizeX, 300, FColor32::White, CX_Left, CY_Bottom);
    InCanvasRenderer->DrawSprite(GameSeaWaveTextureLayerB, 0, 0, ResolutionSizeX, 625, FColor32::White, CX_Left, CY_Bottom);
    InCanvasRenderer->DrawSprite(GameSeaWaveTextureLayerC, 0, 0, ResolutionSizeX, 850, FColor32::White, CX_Left, CY_Bottom);
    InCanvasRenderer->DrawSprite(GameSeaWaveTextureLayerD, 0, 0, ResolutionSizeX, 850, FColor32::White, CX_Left, CY_Bottom);
    InCanvasRenderer->DrawSprite(GameScoreTexture, 400, 20, 60, 70, FColor32::White);
    InCanvasRenderer->DrawText(FontCache, 1.2f, ScoreCounterString, 470, 35, FColor32::White);


    FGameCharCodeMap::Get()->SetGameLanguage(GL_Greek);
    InCanvasRenderer->DrawText(FontCache, 1.2f, "GYROS", 780, 34, FColor32::White);
    InCanvasRenderer->DrawText(FontCache, 1.2f, RoundCounterString, 1020, 35, FColor32::White);
   
    for (uint32 Index = 0; Index < 6; ++Index)
    {
        FColor32 ColorAndOpacity = Index < LifeCount ? FColor32::White : FColor32::Black;
        InCanvasRenderer->DrawSprite(HeartTexture, -600 + Index * 100, 20, 80, 70, ColorAndOpacity, CX_Right, CY_Top);
    }
   
    InCanvasRenderer->DrawSprite(GameMainBodyShadowTexture, 548, 300, 62, 125, FColor32::White);

    InCanvasRenderer->DrawSprite(GameHandLeftShadowTexture, 529, 308, 32, 150, FColor32::White);
    InCanvasRenderer->DrawSprite(GameHandLeftTexture, 528, 308, 30, 150, FColor32::White);

    InCanvasRenderer->DrawSprite(GameHandRightShadowTexture, 600, 308, 32, 150, FColor32::White);
    InCanvasRenderer->DrawSprite(GameHandRightTexture, 599, 308, 30, 150, FColor32::White);

    InCanvasRenderer->DrawSprite(GameLegLeftShadowTexture, 548, 390, 32, 225, FColor32::White);
    InCanvasRenderer->DrawSprite(GameLegLeftTexture, 547, 390, 30, 225, FColor32::White);

    InCanvasRenderer->DrawSprite(GameLegRightShadowTexture, 578, 390, 32, 225, FColor32::White);
    InCanvasRenderer->DrawSprite(GameLegRightTexture, 577, 390, 30, 225, FColor32::White);

    InCanvasRenderer->DrawSprite(GameHeadShadowTexture, 527, 205, 100, 105, FColor32::White);
    InCanvasRenderer->DrawSprite(GameHeadTexture, 527, 205, 100, 105, FColor32::White);

    InCanvasRenderer->DrawSprite(GameSunglassesTexture, 542, 235, 76, 26, FColor32::White);
    InCanvasRenderer->DrawSprite(GameMainBodyTexture, 547, 300, 60, 125, FColor32::White);

    static const uint8 MAXLETTERSIZE = 12;
    const uint8 GameWordLength = GameWord.GetLength();
    static const uint16 PosX          = 830;
    static uint16 FirstRowPosX        = PosX;
    uint16 SecondRowPosX       = PosX;
    static const uint16 FirstRowPosY  = 230;
    static const uint16 SecondRowPosY = 300;
    bool isTwoWords = false;
    uint8 FirstWordSize = 0;
    uint8 SecondWordSize = 0;
    uint16 WordIndex = 0;
    uint16 DrawIndex = 0;

    for (WordIndex = 0; WordIndex < GameWordLength; ++WordIndex)
    {
        const TCHAR &Letter = GameWord[WordIndex];
        if (Letter == ' ')
        {
            FirstWordSize = WordIndex;
            SecondWordSize = GameWordLength - WordIndex - 1;
            if (FirstWordSize + SecondWordSize > MAXLETTERSIZE)
            {
                isTwoWords = true;
            }
            continue;
        }

        if (isTwoWords)
        {
                InCanvasRenderer->DrawSprite(GameEmptyLetterTexture, SecondRowPosX, SecondRowPosY, 60, 5, FColor32::White);
                SecondRowPosX += 85;
        }

        else
        {
            InCanvasRenderer->DrawSprite(GameEmptyLetterTexture, FirstRowPosX, FirstRowPosY, 60, 5, FColor32::White);
            FirstRowPosX = PosX + WordIndex * 85;
        }

        if (bIsLetterFound[WordIndex])
        {
            if (isTwoWords)
            {
                DrawIndex = WordIndex - FirstWordSize - 1;
                InCanvasRenderer->DrawText(FontCache, 1, Letter, 845 + DrawIndex * 85, 250, FColor32::White);
            }
            else
            {
                DrawIndex = WordIndex;
                InCanvasRenderer->DrawText(FontCache, 1, Letter, 845 + DrawIndex * 85, 180, FColor32::White);
            }
            
        }
    }   

    if (bShowHint)
    {
        InCanvasRenderer->DrawText(FontCache, 0.5, Hint, -30, 150, FColor32::Gray, CX_Right, CY_Center);

        DrawHintMs -= FApplication::Get()->GetTimeElapsed();
        if (DrawHintMs <= 0)
        {
            bShowHint = false;
        }
    }

    FCanvasMenu::Render(InCanvasRenderer);
}