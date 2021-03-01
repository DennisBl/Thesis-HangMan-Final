#ifndef WINDOWS_APPLICATION_H
#define WINDOWS_APPLICATION_H

#include <CoreMinimal.h>

class FWindow;

struct FKeyState
{
	bool bIsDown;
	bool bIsUp;
};

class FApplication
{
public:
	FKeyState KeyStates[256];
	bool bIsCloseRequested;

public:
	static FApplication *Get();

	void RequestClose();
	bool IsCloseRequested();
	void ProcessPendingEvents();
	void GetApplicationResolution(int32 *OutResolutionSizeX, int32 *OutResolutionSizeY);
	void GetCursorPos(FWindow *Window, int32 *OutCursorX, int32 *OutCursorY);
	void GetMouseState(uint16 *bOutIsClicked);
	void SetTimeElapsed(double TimeElapsed);
	bool IsKeyDown(uint16 KeyCode) const;
	bool IsKeyUp(uint16 KeyCode) const;
	void UpdateKeyState();

	double GetTimeElapsed();
};

#endif