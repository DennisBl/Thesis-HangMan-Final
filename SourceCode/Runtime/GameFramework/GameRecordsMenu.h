#ifndef GAME_RECORDS_H
#define GAME_RECORDS_H

#include "GameCore.h"

struct FGameRecord
{
	FString Name;
	int32 Gender;
	int32 BenchScore;
	int32 PeakStreak;
};

class FRecordsMenu : public FCanvasMenu
{
public:
	FString PlayerName;
	FGameRecord GameRecord;

	bool bIsNameValid;
	bool bDrawInvalidName;

public:
	FRecordsMenu();

	virtual void ReInitialize() override;
	virtual void Render(FCanvasRenderer *InCanvasRenderer) override;
};


#endif