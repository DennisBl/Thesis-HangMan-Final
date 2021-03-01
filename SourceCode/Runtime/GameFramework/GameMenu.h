#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "GameCore.h"

enum EBodyState
{
    BS_Alive,
    BS_Dead,
};

class FGameMenu : public FCanvasMenu
{
    enum
    {
        MaximumGameLetterCount = 24
    };

public:
    FString Hint;
    FString GameWord;

    uint32 bIsLetterFound[MaximumGameLetterCount];
    uint32 LifeCount;
    uint32 RoundCounter;
    
    int32 bShowHint;
    int32 DrawHintMs;

    EBodyState HeadState;
    EBodyState HandRightState;
    EBodyState HandLeftState;
    EBodyState MainBodyState;
    EBodyState LegLeftState;
    EBodyState LegRightState;

public:
    FGameMenu();

    void InitializeState();
    bool UpdateState(const TCHAR &InLetter);

    virtual void Render(FCanvasRenderer *InCanvasRenderer) override;
};

#endif