#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "FreeType.lib")

#include <Platform.h>
#include <OpenGL.h>
#include <Renderer.h>
#include <GameFramework.h>
#include <AssetFramework.h>

int WINAPI 
WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int CommandShow)
{
    ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
   
    FPlatformTime::Initialize();
	InitPlatformOpenGL();

    

    

    FWindowInitializer Initializer;
    Initializer.TitleText      = "Thesis";
    Initializer.X              = 800;
    Initializer.Y              = 400;
    Initializer.SizeX          = 1920;
    Initializer.SizeY          = 1080;
    Initializer.WindowMode     = WM_Windowed;
    Initializer.bAllowResizing = true;
    Initializer.bAllowDrag     = true;
    Initializer.bShowMinimize  = true;
    Initializer.bShowMaximize  = true;
    Initializer.bShowClose     = true;
    FWindow *Window = new FWindow(Initializer);

    FRenderContext RenderContext;
    CreateRenderContext(&RenderContext, Window->GetDeviceContext());
    MakeRenderContextCurrent(&RenderContext);

    FCanvasRenderer *CanvasRenderer = new FCanvasRenderer();

    FGameState *GameState = new FGameState();
    GameState->AddMenu(new FMainMenu());
    GameState->AddMenu(new FPlayMenu());
    GameState->AddMenu(new FRecordsMenu());
    GameState->AddMenu(new FGameMenu());
    GameState->AddMenu(new FWinMenu());
    GameState->AddMenu(new FLoseMenu());

    FInputState *InputState = new FInputState();
    while (!FApplication::Get()->IsCloseRequested())
    {
        FPlatformTime::Tick();
        FApplication::Get()->UpdateKeyState();

        FApplication::Get()->ProcessPendingEvents();
        FRenderResourceAllocator::Get()->TickPendingResources();

        bool bIsClickedPrevTick = InputState->bIsClicked;
        FApplication::Get()->GetCursorPos(Window, &InputState->CursorX, &InputState->CursorY);
        FApplication::Get()->GetMouseState(&InputState->bIsClicked);
        InputState->bIsReleased = bIsClickedPrevTick && !InputState->bIsClicked;

        FOpenGL::Clear(FColor32::Black);
        {
            GameState->UpdateAndRender(CanvasRenderer, InputState);

            CanvasRenderer->FlushToViewport();
        }
       
        FOpenGL::Present(Window);

        double CurrentTimeElapsed = FPlatformTime::MilliSeconds();
        FApplication::Get()->SetTimeElapsed(CurrentTimeElapsed);
    }

    FAssetManager::Get()->FreeResources();

    ReleaseRenderContext(&RenderContext);
    MakeRenderContextCurrent(0);

    delete GameState;
    delete InputState;
    delete Window;

	return 0;
}