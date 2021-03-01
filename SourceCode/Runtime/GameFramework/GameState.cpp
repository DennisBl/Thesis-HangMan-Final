#include "GameState.h"

FGameState::FGameState()
	: BenchScore(0)
	, CurrentStreak(0)
{ }

void
FGameState::ReInitialize()
{
	PlayerName.Empty();
	BenchScore    = 0;
	CurrentStreak = 0;

	FCanvasMenuState::ReInitialize();
}
