#include "WindowsWindow.h"
#include "WindowsApplication.h"

static LRESULT CALLBACK
WindowMessageProc(HWND Window, uint32 Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CLOSE:
	{
		FApplication::Get()->RequestClose();
	} break;

	case WM_KEYDOWN:
	{
		FKeyState *KeyStates = FApplication::Get()->KeyStates;
		KeyStates[wParam].bIsDown = true;
	} break;

	case WM_KEYUP:
	{
		FKeyState *KeyStates = FApplication::Get()->KeyStates;
		KeyStates[wParam].bIsUp = true;
	} break;
	}

	return DefWindowProc(Window, Message, wParam, lParam);
}

static void
InitializeWindowsClass()
{
	static bool bIsInitialized;
	if (!bIsInitialized)
	{ 
		HINSTANCE Instance = ::GetModuleHandle(0);

		WNDCLASS WindowClass;
		FMemory::Zero(&WindowClass, sizeof(WNDCLASS));
		WindowClass.style		  = CS_OWNDC;
 		WindowClass.lpfnWndProc	  = WindowMessageProc;
		WindowClass.cbClsExtra	  = 0;
		WindowClass.cbWndExtra	  = 0;
		WindowClass.hInstance     = Instance;
		WindowClass.hIcon		  = LoadIcon(Instance, IDI_APPLICATION);
		WindowClass.hCursor		  = LoadCursor(0, IDC_ARROW);
		WindowClass.hbrBackground = 0;
		WindowClass.lpszMenuName  = 0;
		WindowClass.lpszClassName = "WindowClass";
		::RegisterClass(&WindowClass);
	
		bIsInitialized = true;
	}
}

FWindow::FWindow(const FWindowInitializer &Initializer)
	: WindowHandle(0)
	, DeviceContext(0)
{
	InitializeWindowsClass();

	const TCHAR *WindowTitle = Initializer.TitleText.GetData();
	WindowHandle = ::CreateWindowEx(
		0,
		"WindowClass",
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		Initializer.X, 
		Initializer.Y,
		Initializer.SizeX, 
		Initializer.SizeY,
		0,
		0,
		GetModuleHandle(0),
		0);
	DeviceContext = ::GetDC(WindowHandle);

	::ShowWindow(WindowHandle, SW_SHOW);
}

FWindow::~FWindow()
{
	::ReleaseDC(WindowHandle, DeviceContext);
	::DestroyWindow(WindowHandle);
}