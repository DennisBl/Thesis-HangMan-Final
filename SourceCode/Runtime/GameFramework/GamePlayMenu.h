#ifndef GAME_PLAY_MENU_H
#define GAME_PLAY_MENU_H

#include "GameCore.h"

enum EPlayGender
{
    PG_Boy,
    PG_Girl,
};

enum EPlayCategory
{
    PC_History,
    PC_Music,
    PC_Geography,
};

enum EPlayMode
{
    PM_Easy,
    PM_Medium,
    PM_Hard
};

class FPlayMenu : public FCanvasMenu
{
public:
    FString PlayerName;
    int32 PlayGender;
    int32 PlayCategory;
    int32 PlayMode;

    bool bIsInPlay;
    bool bIsNameValid;

public:
    FPlayMenu();

    virtual void ReInitialize() override;
    virtual void Render(FCanvasRenderer *InCanvasRenderer) override;
};

#endif