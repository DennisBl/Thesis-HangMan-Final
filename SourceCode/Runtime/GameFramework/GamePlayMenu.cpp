#include "GamePlayMenu.h"
#include "GameMenu.h"
#include "GameState.h"
#include "GameCharCodeMap.h"

#include <AssetFramework.h>

struct FCategoryGameWord
{
    EPlayCategory Category;
    FString Hint;
    FString GameWord;

    FORCEINLINE FCategoryGameWord()
    { }

    FORCEINLINE FCategoryGameWord(EPlayCategory Category, const FString &Hint, const FString &GameWord)
        : Category(Category)
        , Hint(Hint)
        , GameWord(GameWord)
    { }
};

static const FCategoryGameWord GameWordPerCategory[] =
{
    FCategoryGameWord(PC_History,   "HRVAS TRVIKOY POLEMOY", " AXILLEAS"),
    FCategoryGameWord(PC_History,   "DIASHMOS DIKTATORAS", "ADOLFOS XITLER"),
    FCategoryGameWord(PC_History,   "ARXAIOS ELLINAS HMIUEOS", "HRAKLHS"),
    FCategoryGameWord(PC_History,   "UEOS TOY OLYMPOY", "HFAISTOS"),
    FCategoryGameWord(PC_History,   "POLEMOS ANEJARTHSIAS", "UEODVROS KOLOKOTRVNIS"),
    FCategoryGameWord(PC_History,   "BYZANTIO", "KVNSTANTINOS PALAIOLOGOS"),
    FCategoryGameWord(PC_History,   "ARXAIOS ELLINAS SIGGRAFEAS", "OMHROS"),
    FCategoryGameWord(PC_History,   "URHSKEYTIKH GIORTH", "OLYMPIAKOI AGVNES"),
    FCategoryGameWord(PC_History,   "POLEMOS", "POLEMOS BIETNAM"),
    FCategoryGameWord(PC_History,   "POLEMOS ANEJARTHSIAS", "DHMHTRIOS YCHLANTHS"),

    FCategoryGameWord(PC_Music,     "ELLHNAS TRAGOYDISTHS", "SAKHS ROUBAS"),
    FCategoryGameWord(PC_Music,     "AMERIKANOS TRAGOYDISTHS", "MALOYMA"),
    FCategoryGameWord(PC_Music,     "MOYSIKO ORGANO", "KIUARA"),
    FCategoryGameWord(PC_Music,     "MOYSIKO ORGANO", "PIANO"),
    FCategoryGameWord(PC_Music,     "ELLHNAS TRAGOYDISTHS", "KVNSTANTINOS PANTELIDHS"),
    FCategoryGameWord(PC_Music,     "DIASHMOS TRAGOYDISTHS", "MAIKL TZAKSON"),
    FCategoryGameWord(PC_Music,     "MOYSIKH EKDHLVSH", "GIOYROBIZION"),
    FCategoryGameWord(PC_Music,     "TYPOS MOYSIKHS", "POP ROK"),
    FCategoryGameWord(PC_Music,     "TYPOS MOYSIKHS", "XIP XOP"),
    FCategoryGameWord(PC_Music,     "TYPOS MOYSIKHS", "KLASSIKH"),
    

    FCategoryGameWord(PC_Geography, "DIEUNHS PODOSFAIRIKH OMADA", "BRAZILIA"),
    FCategoryGameWord(PC_Geography, "EYRVPH", "ELLADA"),
    FCategoryGameWord(PC_Geography, "HPEIROS", "EYRVPH"),
    FCategoryGameWord(PC_Geography, "AFRIKH", "AIUIOPIA"),
    FCategoryGameWord(PC_Geography, "ASIA", "KINA"),
    FCategoryGameWord(PC_Geography, "PRVTEYOYSA", "AUHNA"),
    FCategoryGameWord(PC_Geography, "PRVTEYOYSA", "BEROLINO"),
    FCategoryGameWord(PC_Geography, "BOREIA AMERIKH", "GROILANDIA"),
    FCategoryGameWord(PC_Geography, "NOTIA AMERIKH", "ARGETINH"),
    FCategoryGameWord(PC_Geography, "PRVTEYOYSA", "MPOYENOS AIRES"),
};

static void GetGameWordArrayByCategory(TArray<FCategoryGameWord> &OutArray, int32 Category)
{
    for (uint32 Index = 0; Index < ArrayCount(GameWordPerCategory); ++Index)
    {
        const FCategoryGameWord &CategoryGameWord = GameWordPerCategory[Index];
        if (Category == CategoryGameWord.Category)
        {
            OutArray.Add(CategoryGameWord);
        }
    }
}

class FHomeButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FCanvasMenuState* MenuState = OwnerMenu->GetMenuState();
        MenuState->MenuCategory = MC_MainMenu;
    }
};

class FEnumSelectionPreviousButton : public FCanvasButton
{
public:
    int32 *Value;
    int32 Min;
    int32 Max;

public:
    FEnumSelectionPreviousButton(int32 *InValue, int32 InMin, int32 InMax);

    virtual void OnRelease() override;
};

class FEnumSelectionNextButton : public FCanvasButton
{
public:
    int32 *Value;
    int32 Min;
    int32 Max;

public:
    FEnumSelectionNextButton(int32 *InValue, int32 InMin, int32 InMax);

    virtual void OnRelease() override;
};

FEnumSelectionPreviousButton::FEnumSelectionPreviousButton(int32 *InValue, int32 InMin, int32 InMax)
    : Value(InValue)
    , Min(InMin)
    , Max(InMax)
{ }

void
FEnumSelectionPreviousButton::OnRelease()
{
    *Value = FMath::CircularClamp<int32>(--(*Value), Min, Max);
}

FEnumSelectionNextButton::FEnumSelectionNextButton(int32 *InValue, int32 InMin, int32 InMax)
    : Value(InValue)
    , Min(InMin)
    , Max(InMax)
{ }

void
FEnumSelectionNextButton::OnRelease()
{
    *Value = FMath::CircularClamp<int32>(++(*Value), Min, Max);
}

class FPlayMenuTickButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FPlayMenu *PlayMenu = (FPlayMenu *)OwnerMenu;
        if (PlayMenu->bIsNameValid)
        { 
            FCanvasMenuState *MenuState = GetMenuState();
            MenuState->MenuCategory = MC_GameMenu;

            uint32 LifeCount = 0;
            switch (PlayMenu->PlayMode)
            {
            case PM_Easy:
                LifeCount = 0xFFFFFFFF;
                break;
            case PM_Medium:
                LifeCount = 6;
                break;
            case PM_Hard:
                LifeCount = 1;
                break;
            }

            TArray<FCategoryGameWord> GameWordArary;
            GetGameWordArrayByCategory(GameWordArary, PlayMenu->PlayCategory);

            float GameWordMinIndex = 0.0f;
            float GameWordMaxIndex = static_cast<float>(GameWordArary.GetCount() - 1);
            uint32 GameWordIndex = static_cast<uint32>(FMath::Random(GameWordMinIndex, GameWordMaxIndex));

            FString Hint = GameWordArary[GameWordIndex].Hint;
            FString GameWord = GameWordArary[GameWordIndex].GameWord;

            FGameState *GameState = (FGameState *)MenuState;
            GameState->PlayerName = PlayMenu->PlayerName;

            FGameMenu *GameMenu = (FGameMenu *)MenuState->GetMenuById(MC_GameMenu);
            GameMenu->InitializeState();
            GameMenu->LifeCount = LifeCount;
            GameMenu->Hint      = Hint;
            GameMenu->GameWord  = GameWord;
        }
    }
};

class FNameButton : public FCanvasButton
{
    enum
    {
        MinNameCharCount = 3
    };

public:
    const FFontCache *FontCache;
    float FontScale;
    FColor32 ColorAndOpacity;

public:
    virtual void Render(FCanvasRenderer *InCanvasRenderer) override
    {
        FString &PlayerName = GetPlayerName();

        FPlayMenu *PlayMenu = (FPlayMenu *)OwnerMenu;
        if (!PlayMenu->bIsInPlay)
        {
            for (const FCharCodeMap& CharKeyCode : GreekCharCodeMap)
            {
                if (FGameCharCodeMap::Get()->IsCharCodePresent(CharKeyCode))
                {
                    const TCHAR& KeyCode = CharKeyCode.KeyCode;
                    if (FApplication::Get()->IsKeyDown(KeyCode))
                    {
                        PlayerName.Append(KeyCode);
                    }
                }
            }

            if (FApplication::Get()->IsKeyDown(VK_BACK) && !PlayerName.IsEmpty())
            {
                uint32 NewSize = PlayerName.GetLength() - 1;
                PlayerName.Resize(NewSize);
            }
        }

        bool bIsNameValid = IsValid();
        PlayMenu->bIsNameValid = bIsNameValid;
        if (bIsNameValid)
        {
            const int32 X = Position.GetOriginX();
            const int32 Y = Position.GetOriginY();
            InCanvasRenderer->DrawText(FontCache, FontScale, PlayerName, X, Y, ColorAndOpacity, AlignX, AlignY);
        }
        else if (PlayerName.IsEmpty())
        {
            FString NullHint;
            NullHint.Append("PLHKTROLOGHSE ONOMA MEGALYTERO APO ");
            NullHint.Append(FString(MinNameCharCount));
            NullHint.Append(" XARAKTHRES POY JEKINAEI ME GRAMMA");

            const int32 X = Position.GetOriginX();
            const int32 Y = Position.GetOriginY();
            InCanvasRenderer->DrawText(FontCache, 0.6, NullHint, X, Y, FColor32::Green, AlignX, AlignY);
        }
        else
        {
            const int32 X = Position.GetOriginX();
            const int32 Y = Position.GetOriginY();
            InCanvasRenderer->DrawText(FontCache, FontScale, PlayerName, X, Y, FColor32::Red, AlignX, AlignY);
        }
    }

    bool IsValid() const
    {
        FString &PlayerName = GetPlayerName();

        bool bIsValid = true;
        if (PlayerName.GetLength() < MinNameCharCount)
        {
            bIsValid = false;
        }
                
        bool bFoundNonNumeric = false;
        for (const TCHAR &Char : PlayerName)
        {
            FString CharString(Char);

            const TCHAR *CharData = CharString.GetData();
            if (CString::IsNumeric(CharData) && !bFoundNonNumeric)
            {
                    bIsValid = false;
            }
            else
            {
                bFoundNonNumeric = true;
            }
        }

        return bIsValid;
    }

private:
    FString &GetPlayerName() const
    {
        FPlayMenu *PlayMenu = (FPlayMenu *)OwnerMenu;
        return PlayMenu->PlayerName;
    }
};

FPlayMenu::FPlayMenu()
    : bIsInPlay(false)
    , bIsNameValid(false)
{
    const FFontCache *FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/Greek.ttf");

    const FTexture2D *LeftArrowTexture  = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/PROFILE/LEFT ARROW.png");
    const FTexture2D *RightArrowTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/PROFILE/RIGHT ARROW.png");
    const FTexture2D *TickTexture       = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/OK.png");
    const FTexture2D *HomeTexture       = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/HOME.png");

    FCanvasButton *GenderSelectPreviousButton = new FEnumSelectionPreviousButton(&PlayGender, PG_Boy, PG_Girl);
    GenderSelectPreviousButton->Position     = FIntRect(-250, 125, -150, 225);
    GenderSelectPreviousButton->AlignX       = CX_Center;
    GenderSelectPreviousButton->AlignY       = CY_Top;
    GenderSelectPreviousButton->NormalBrush  = FContentBrush(LeftArrowTexture, FColor32::White);
    GenderSelectPreviousButton->HoveredBrush = FContentBrush(LeftArrowTexture, FColor32(200, 200, 200, 255));
    GenderSelectPreviousButton->ClickedBrush = FContentBrush(LeftArrowTexture, FColor32::White);
    AddButton(GenderSelectPreviousButton);

    FCanvasButton *GenderSelectNextButton = new FEnumSelectionNextButton(&PlayGender, PG_Boy, PG_Girl);
    GenderSelectNextButton->Position     = FIntRect(250, 125, 350, 225);
    GenderSelectNextButton->AlignX       = CX_Center;
    GenderSelectNextButton->AlignY       = CY_Top;
    GenderSelectNextButton->NormalBrush  = FContentBrush(RightArrowTexture, FColor32::White);
    GenderSelectNextButton->HoveredBrush = FContentBrush(RightArrowTexture, FColor32(200, 200, 200, 255));
    GenderSelectNextButton->ClickedBrush = FContentBrush(RightArrowTexture, FColor32::White);
    AddButton(GenderSelectNextButton);

    FCanvasButton* CategorySelectPreviousButton = new FEnumSelectionPreviousButton(&PlayCategory, PC_History, PC_Geography);
    CategorySelectPreviousButton->Position     = FIntRect(-150, 650, -100, 700);
    CategorySelectPreviousButton->AlignX       = CX_Center;
    CategorySelectPreviousButton->AlignY       = CY_Top;
    CategorySelectPreviousButton->NormalBrush  = FContentBrush(LeftArrowTexture, FColor32::White);
    CategorySelectPreviousButton->HoveredBrush = FContentBrush(LeftArrowTexture, FColor32(200, 200, 200, 255));
    CategorySelectPreviousButton->ClickedBrush = FContentBrush(LeftArrowTexture, FColor32::White);
    AddButton(CategorySelectPreviousButton);

    FCanvasButton* CategorySelectNextButton = new FEnumSelectionNextButton(&PlayCategory, PC_History, PC_Geography);
    CategorySelectNextButton->Position     = FIntRect(150, 650, 200, 700);
    CategorySelectNextButton->AlignX       = CX_Center;
    CategorySelectNextButton->AlignY       = CY_Top;
    CategorySelectNextButton->NormalBrush  = FContentBrush(RightArrowTexture, FColor32::White);
    CategorySelectNextButton->HoveredBrush = FContentBrush(RightArrowTexture, FColor32(200, 200, 200, 255));
    CategorySelectNextButton->ClickedBrush = FContentBrush(RightArrowTexture, FColor32::White);
    AddButton(CategorySelectNextButton);

    FCanvasButton* ModeSelectPreviousButton = new FEnumSelectionPreviousButton(&PlayMode, PM_Easy, PM_Hard);
    ModeSelectPreviousButton->Position     = FIntRect(-150, 825, -100, 880);
    ModeSelectPreviousButton->AlignX       = CX_Center;
    ModeSelectPreviousButton->AlignY       = CY_Top;
    ModeSelectPreviousButton->NormalBrush  = FContentBrush(LeftArrowTexture, FColor32::White);
    ModeSelectPreviousButton->HoveredBrush = FContentBrush(LeftArrowTexture, FColor32(200, 200, 200, 255));
    ModeSelectPreviousButton->ClickedBrush = FContentBrush(LeftArrowTexture, FColor32::White);
    AddButton(ModeSelectPreviousButton);

    FCanvasButton* ModeSelectNextButton = new FEnumSelectionNextButton(&PlayMode, PM_Easy, PM_Hard);
    ModeSelectNextButton->Position     = FIntRect(150, 825, 200, 880);
    ModeSelectNextButton->AlignX       = CX_Center;
    ModeSelectNextButton->AlignY       = CY_Top;
    ModeSelectNextButton->NormalBrush  = FContentBrush(RightArrowTexture, FColor32::White);
    ModeSelectNextButton->HoveredBrush = FContentBrush(RightArrowTexture, FColor32(200, 200, 200, 255));
    ModeSelectNextButton->ClickedBrush = FContentBrush(RightArrowTexture, FColor32::White);
    AddButton(ModeSelectNextButton);

    FNameButton *NameButton = new FNameButton();
    NameButton->FontCache       = FontCache;
    NameButton->FontScale       = 1;
    NameButton->ColorAndOpacity = FColor32(200, 200, 200, 255);
    NameButton->Position        = FIntRect(0, 440, 500, 500);
    NameButton->AlignX          = CX_Center;
    NameButton->AlignY          = CY_Top;
    AddButton(NameButton);

    FCanvasButton *TickButton = new FPlayMenuTickButton();
    TickButton->Position     = FIntRect(0, 925, 75, 1000);
    TickButton->AlignX       = CX_Center;
    TickButton->AlignY       = CY_Top;
    TickButton->NormalBrush  = FContentBrush(TickTexture, FColor32::White);
    TickButton->HoveredBrush = FContentBrush(TickTexture, FColor32(200, 200, 200, 255));
    TickButton->ClickedBrush = FContentBrush(TickTexture, FColor32::White);
    AddButton(TickButton);

    FHomeButton* HomeButton = new FHomeButton();
    HomeButton->Position     = FIntRect(25, 25, 95, 95);
    HomeButton->AlignX       = CX_Left;
    HomeButton->AlignY       = CY_Top;
    HomeButton->NormalBrush  = FContentBrush(HomeTexture, FColor32::White);
    HomeButton->HoveredBrush = FContentBrush(HomeTexture, FColor32(200, 200, 200, 255));
    HomeButton->ClickedBrush = FContentBrush(HomeTexture, FColor32::White);
    AddButton(HomeButton);
}

void
FPlayMenu::ReInitialize()
{
    PlayGender   = 0;
    PlayCategory = 0;
    PlayMode     = 0;

    bIsInPlay = false;
}

void
FPlayMenu::Render(FCanvasRenderer *InCanvasRenderer)
{
    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

    const FTexture2D *BackgroundTextureA = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/0 sea background-.png");
    const FTexture2D *BackgroundTextureB = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/1 deap.png");
    const FTexture2D *BackgroundTextureC = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/WATER TEXTURE.png");
    const FTexture2D *BackgroundTextureD = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/Hangman 4 Final-01.png");
    const FTexture2D *BoyTexture         = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/PROFILE/boy PROFILE.png");
    const FTexture2D *GirlTexture        = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/PROFILE/GIRL PROFILE.png");
    const FTexture2D *NameTexture        = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/NAME/NAME INPUT-GR.png");
    const FTexture2D* LineTexture        = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/LINE.png");
    
    const FTexture2D *Category           = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/Asset 81xhdpi.png");
    const FTexture2D *HistoryTexture     = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/Asset 83xhdpi.png");
    const FTexture2D *GeographyTexture   = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/GEOGRAPHY-gr.png");
    const FTexture2D *MusicTexture       = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/Asset 82xhdpi.png");

    const FTexture2D *ModeTexture        = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/MODE/mode-gr.png");
    const FTexture2D *EasyModeTexture    = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/MODE/easy-gr.png");
    const FTexture2D *MediumModeTexture  = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/MODE/medium-gr.png");
    const FTexture2D *HardModeTexture    = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/Mode/hard-gr.png");

    //English
    /*const FTexture2D* Category = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/Asset 65xhdpi.png");
    const FTexture2D* HistoryTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/Asset 79xhdpi.png");
    const FTexture2D* GeographyTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/GEOGRAPHY.png");
    const FTexture2D* MusicTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/CATEGORY/Asset 80xhdpi.png");

    const FTexture2D* ModeTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/MODE/MODE.png");
    const FTexture2D* EasyModeTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/MODE/easy.png");
    const FTexture2D* MediumModeTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/MODE/medium.png");
    const FTexture2D* HardModeTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/Mode/hard.png");*/

    InCanvasRenderer->DrawSprite(BackgroundTextureA, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureB, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureC, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureD, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(Category, 0, 560, 240, 52, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(ModeTexture, 0, 740, 240, 52, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(NameTexture, 0, 350, 250, 75, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 500, 500, 5, FColor32::White, CX_Center, CY_Top);

    switch (PlayGender)
    {
    case PG_Boy:
        InCanvasRenderer->DrawSprite(BoyTexture, 0, 50, 250, 250, FColor32::White, CX_Center, CY_Top);
        break;
    case PG_Girl:
        InCanvasRenderer->DrawSprite(GirlTexture, 0, 50, 250, 250, FColor32::White, CX_Center, CY_Top);
        break;
    }

    switch (PlayCategory)
    {
    case PC_History:
        InCanvasRenderer->DrawSprite(HistoryTexture, 0, 650, 200, 60, FColor32::White, CX_Center, CY_Top);
        break;
    case PC_Music:
        InCanvasRenderer->DrawSprite(MusicTexture, 0, 650, 200, 60, FColor32::White, CX_Center, CY_Top);
        break;
    case PC_Geography:
        InCanvasRenderer->DrawSprite(GeographyTexture, 0, 650, 240, 60, FColor32::White, CX_Center, CY_Top);
        break;
    }

    switch (PlayMode)
    {
    case PM_Easy:
        InCanvasRenderer->DrawSprite(EasyModeTexture, 0, 825, 190, 55, FColor32::White, CX_Center, CY_Top);
        break;
    case PM_Medium:
        InCanvasRenderer->DrawSprite(MediumModeTexture, 0, 825, 190, 55, FColor32::White, CX_Center, CY_Top);
        break;
    case PM_Hard:
        InCanvasRenderer->DrawSprite(HardModeTexture, 0, 825, 190, 55, FColor32::White, CX_Center, CY_Top);
        break;
    }

    FCanvasMenu::Render(InCanvasRenderer);
}