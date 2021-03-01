#include "GameRecordsMenu.h"

#include <AssetFramework.h>
#include "GameCharCodeMap.h"

class FRecordsNameButton : public FCanvasButton
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

        FRecordsMenu *RecordsMenu = (FRecordsMenu *)OwnerMenu;
        const TCHAR Letters[] =
        {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
        };

        FGameCharCodeMap::Get()->SetGameLanguage(GL_Greek); 

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
   
        bool bIsNameValid = IsValid();
        RecordsMenu->bIsNameValid = bIsNameValid;
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

            //English
            /*FString NullHint
            NullHint.Append("Enter a name larger than ");
            NullHint.Append(FString(MinNameCharCount));
            NullHint.Append(" characters and start with a letter.");*/

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

    bool IsValid()
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
    FString &GetPlayerName()
    {
        FRecordsMenu *RecordsMenu = (FRecordsMenu *)OwnerMenu;
        return RecordsMenu->PlayerName;
    }
};


class FHomeButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FRecordsMenu* RecordsMenu = (FRecordsMenu*)OwnerMenu;
        RecordsMenu->ReInitialize();
        FCanvasMenuState* MenuState = OwnerMenu->GetMenuState();
        MenuState->MenuCategory = MC_MainMenu;
    }
};

class FTickButton : public FCanvasButton
{
public:
    virtual void OnRelease() override
    {
        FRecordsMenu *RecordsMenu = (FRecordsMenu *)OwnerMenu;
        if (RecordsMenu->bIsNameValid)
        {
            FString &PlayerName = GetPlayerName();

            FPlatformFileIni RecordsFile("../Records.ini");
            if (RecordsFile.Exists(PlayerName))
            {
                RecordsFile.BeginReadback(PlayerName);
                int32 BenchScore = RecordsFile.ReadInteger("BenchScore");
                int32 PeakStreak = RecordsFile.ReadInteger("PeakStreak");
                RecordsFile.EndReadback();

                FRecordsMenu *RecordsMenu = (FRecordsMenu *)OwnerMenu;
                RecordsMenu->bDrawInvalidName = false;

                FGameRecord &GameRecord = RecordsMenu->GameRecord;
                GameRecord.Name = PlayerName;
                GameRecord.BenchScore = BenchScore;
                GameRecord.PeakStreak = PeakStreak;
            }
            else
            {
                FRecordsMenu *RecordsMenu = (FRecordsMenu *)OwnerMenu;
                RecordsMenu->bDrawInvalidName = true;
            }
        }
    }

private:
    FString &GetPlayerName()
    {
        FRecordsMenu *RecordsMenu = (FRecordsMenu *)OwnerMenu;
        return RecordsMenu->PlayerName;
    }
};

void
FRecordsMenu::ReInitialize()
{
    PlayerName.Empty();
    GameRecord.Name.Empty();
    GameRecord.BenchScore = 0;
    GameRecord.PeakStreak = 0;
    bDrawInvalidName = false;
}

FRecordsMenu::FRecordsMenu()
    : bIsNameValid(false)
    , bDrawInvalidName(false)
{
    const FFontCache *FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/Greek.ttf");

    const FTexture2D *TickTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/OK.png");

    FRecordsNameButton*NameButton = new FRecordsNameButton();
    NameButton->FontCache       = FontCache;
    NameButton->FontScale       = 1;
    NameButton->ColorAndOpacity = FColor32(200, 200, 200, 255);
    NameButton->Position        = FIntRect(0, 150, 500, 200);
    NameButton->AlignX          = CX_Center;
    NameButton->AlignY          = CY_Top;
    AddButton(NameButton);

    FCanvasButton *TickButton = new FTickButton();
    TickButton->Position    = FIntRect(0, 250, 75, 325);
    TickButton->AlignX      = CX_Center;
    TickButton->AlignY      = CY_Top;
    TickButton->NormalBrush = FContentBrush(TickTexture, FColor32::White);
    TickButton->HoveredBrush = FContentBrush(TickTexture, FColor32(200, 200, 200, 255));
    TickButton->ClickedBrush = FContentBrush(TickTexture, FColor32::White);
    AddButton(TickButton);

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
FRecordsMenu::Render(FCanvasRenderer *InCanvasRenderer)
{
    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

    const FFontCache *FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/Greek.ttf");
   // const FFontCache* FontCache = FAssetManager::Get()->FindOrCreateFontCache("Fonts/ComicSansMSBold.ttf");

    const FTexture2D *BackgroundTextureA = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/0 sea background-.png");
    const FTexture2D *BackgroundTextureB = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/1 deap.png");
    const FTexture2D *BackgroundTextureC = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/WATER TEXTURE.png");
    const FTexture2D *BackgroundTextureD = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/0 Sea Background/Sea Background layers/Hangman 4 Final-01.png");
    
    //English
    //const FTexture2D *NameTexture      = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/NAME/NAME INPUT.png");   
   // const FTexture2D *LineTexture      = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/LINE.png");

   const FTexture2D* NameTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/1 Buttons/FRONT MENU/0 PLAY/PLAYER/NAME/NAME INPUT-GR.png");
   const FTexture2D* LineTexture = FAssetManager::Get()->FindOrCreateTexture2D("Images/Game Hangman/MENU/2 Background/BUTTONS BACKGROUND/CORRECT ANSWER/LINE.png");

    InCanvasRenderer->DrawSprite(BackgroundTextureA, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureB, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureC, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);
    InCanvasRenderer->DrawSprite(BackgroundTextureD, 0, 0, ResolutionSizeX, ResolutionSizeY, FColor32::White);

    InCanvasRenderer->DrawSprite(NameTexture, 0, 50, 250, 75, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 200, 500, 5, FColor32::White, CX_Center, CY_Top);

    InCanvasRenderer->DrawText(FontCache, 1.2f, "Skor", 0, 400, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 550, 300, 5, FColor32::White, CX_Center, CY_Top);

    InCanvasRenderer->DrawText(FontCache, 1.2f, "Seri", 0, 625, FColor32::White, CX_Center, CY_Top);
    InCanvasRenderer->DrawSprite(LineTexture, 0, 775, 300, 5, FColor32::White, CX_Center, CY_Top);

    FString BenchScoreString(GameRecord.BenchScore);
    InCanvasRenderer->DrawText(FontCache, 1, BenchScoreString, 0, 500, FColor32(200, 200, 200, 255), CX_Center, CY_Top);

    FString PeakStreakString(GameRecord.PeakStreak);
    InCanvasRenderer->DrawText(FontCache, 1, PeakStreakString, 0, 725, FColor32(200, 200, 200, 255), CX_Center, CY_Top);

    if (bDrawInvalidName)
    {
        InCanvasRenderer->DrawText(FontCache, 1, "PAIXTHS DEN BREUHKE", 0, -50, FColor32::Red, CX_Center, CY_Bottom);
    }

	FCanvasMenu::Render(InCanvasRenderer);
}