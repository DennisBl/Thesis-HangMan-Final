#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <CoreMinimal.h>

enum EWindowMode
{
	WM_Windowed,
	WM_Fullscreen,
	WM_FullscreenExclusive
};

struct FWindowInitializer
{
	FString TitleText;
	int32 X;
	int32 Y;
	int32 SizeX;
	int32 SizeY;
	EWindowMode WindowMode;

	int32 bAllowResizing : 1;
	int32 bAllowDrag     : 1;
	int32 bShowMinimize  : 1;
	int32 bShowMaximize  : 1;
	int32 bShowClose     : 1;
};

class FWindow
{
public:
	FWindow(const FWindowInitializer &Initializer);
	~FWindow();

	FORCEINLINE HWND GetWindowHandle() const
	{
		return WindowHandle;
	}

	FORCEINLINE HDC GetDeviceContext() const
	{
		return DeviceContext;
	}

private:
	HWND WindowHandle;
	HDC DeviceContext;
};

#endif