#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameCore.h"

class FGameState : public FCanvasMenuState
{
public:
	FString PlayerName;
	int32 BenchScore;
	int32 CurrentStreak;

public:
	FGameState();

	virtual void ReInitialize() override;
};

#endif