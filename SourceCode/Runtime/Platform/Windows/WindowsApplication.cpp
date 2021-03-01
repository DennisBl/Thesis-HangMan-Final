#include "WindowsApplication.h"
#include "WindowsWindow.h"

static FApplication ApplicationGlobal;

static const int32 ResolutionSizeX = 1898; 
static const int32 ResolutionSizeY = 1024; 

static double CurrentTimeElapsed = 0;

FApplication *
FApplication::Get()
{
	return &ApplicationGlobal;
}

void 
FApplication::RequestClose()
{
    bIsCloseRequested = true;
}

bool
FApplication::IsCloseRequested()
{
    return bIsCloseRequested;
}

void
FApplication::ProcessPendingEvents()
{
    MSG Message;
    while (PeekMessageA(&Message, 0, 0, UINT32_MAX, PM_REMOVE))
    {
        TranslateMessage(&Message);
        DispatchMessageA(&Message);
    }
}

void
FApplication::GetApplicationResolution(int32 *OutResolutionSizeX, int32 *OutResolutionSizeY)
{
    *OutResolutionSizeX = ResolutionSizeX;
    *OutResolutionSizeY = ResolutionSizeY;
}

void
FApplication::GetCursorPos(FWindow *Window, int32 *OutCursorX, int32 *OutCursorY)
{
    POINT CursorPos;
    ::GetCursorPos(&CursorPos);

    HWND WindowHandle = Window->GetWindowHandle();
    ::ScreenToClient(WindowHandle, &CursorPos);

    *OutCursorX = CursorPos.x;
    *OutCursorY = ResolutionSizeY - CursorPos.y;
}

void
FApplication::GetMouseState(uint16 *bOutIsClicked)
{
    *bOutIsClicked  = GetAsyncKeyState(VK_LBUTTON) != 0;
}

void
FApplication::SetTimeElapsed(double TimeElapsed)
{
    CurrentTimeElapsed = TimeElapsed;
}

double
FApplication::GetTimeElapsed()
{
    return CurrentTimeElapsed;
}

bool 
FApplication::IsKeyDown(uint16 KeyCode) const
{
    Assert(KeyCode < 255);
    return KeyStates[KeyCode].bIsDown;
}

bool 
FApplication::IsKeyUp(uint16 KeyCode) const
{
    Assert(KeyCode < 255);
    return KeyStates[KeyCode].bIsUp;
}

void
FApplication::UpdateKeyState()
{
    FMemory::Zero(KeyStates, sizeof(KeyStates));
}