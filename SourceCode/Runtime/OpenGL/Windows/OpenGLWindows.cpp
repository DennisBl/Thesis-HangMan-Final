#include "OpenGLWindows.h"

static const int32 OpenGLVersionMajor = 4;
static const int32 OpenGLVersionMinor = 5;

static LRESULT CALLBACK 
WindowMessageProc(HWND Window, uint32 Message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(Window, Message, wParam, lParam);
}

static void 
CreateOpenGLContextWindow(FRenderContext *InOutContext)
{
	WNDCLASS WindowClass = {};
	WindowClass.style         = CS_OWNDC;
	WindowClass.lpfnWndProc   = WindowMessageProc;
	WindowClass.cbClsExtra    = 0;
	WindowClass.cbWndExtra    = 0;
	WindowClass.hInstance     = 0;
	WindowClass.hIcon         = 0;
	WindowClass.hCursor       = 0;
	WindowClass.hbrBackground = 0;
	WindowClass.lpszMenuName  = 0;
	WindowClass.lpszClassName = "DummyWindow";
	::RegisterClass(&WindowClass);

	InOutContext->WindowHandle = CreateWindowEx(
		WS_EX_WINDOWEDGE,
		"DummyWindow",
		0,
		WS_POPUP,
		0, 0, 1, 1,
		0, 0, 0, 0);
	HDC DeviceContext = GetDC(InOutContext->WindowHandle);

	PIXELFORMATDESCRIPTOR PixelFormatDesc = {};
	PixelFormatDesc.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
	PixelFormatDesc.nVersion     = 1;
	PixelFormatDesc.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	PixelFormatDesc.iPixelType   = PFD_TYPE_RGBA;
	PixelFormatDesc.cColorBits   = 32;
	PixelFormatDesc.cDepthBits   = 0;
	PixelFormatDesc.cStencilBits = 0;
	PixelFormatDesc.iLayerType   = PFD_MAIN_PLANE;

	int32 PixelFormat = ::ChoosePixelFormat(DeviceContext, &PixelFormatDesc);
	::SetPixelFormat(DeviceContext, PixelFormat, &PixelFormatDesc);

	InOutContext->DeviceContext = DeviceContext;
	InOutContext->RenderContext = wglCreateContext(DeviceContext);
	wglMakeCurrent(DeviceContext, InOutContext->RenderContext);
}

static void
ReleaseOpenGLContextWindow(FRenderContext *InOutContext)
{
	::ReleaseDC(InOutContext->WindowHandle, InOutContext->DeviceContext);
	::DestroyWindow(InOutContext->WindowHandle);
}

static void
InitializeOpenGLEntryPoints(FRenderContext *InOutContext)
{
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglDeleteContext(InOutContext->RenderContext);
	wglMakeCurrent(0, 0);

	int32 ExternalFlags = 0;
#if DEBUG
	ExternalFlags = WGL_CONTEXT_DEBUG_BIT_ARB;
#endif

	int32 AttribList[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 5,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | ExternalFlags,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	InOutContext->RenderContext = wglCreateContextAttribsARB(InOutContext->DeviceContext, 0, AttribList);
	wglMakeCurrent(InOutContext->DeviceContext, InOutContext->RenderContext);

	HMODULE Library = ::LoadLibrary("opengl32.dll");
#define GET_GL_ENTRYPOINTS_DLL(Type, Func) Func = (Type)(void *)::GetProcAddress(Library, #Func);
	GL_ENTRYPOINTS_DLL(GET_GL_ENTRYPOINTS_DLL);
#undef GET_GL_ENTRYPOINTS_DLL
	::FreeLibrary(Library);

#define GET_GL_ENTRYPOINTS(Type,Func) Func = (Type)wglGetProcAddress(#Func);
	GL_ENTRYPOINTS(GET_GL_ENTRYPOINTS);
#undef GET_GL_ENTRYPOINTS

	bool bFoundAllEntryPoints = true;
#define CHECK_GL_ENTRYPOINTS(Type,Func) if (Func == 0) { bFoundAllEntryPoints = false; } 
	GL_ENTRYPOINTS_DLL(CHECK_GL_ENTRYPOINTS);
	GL_ENTRYPOINTS(CHECK_GL_ENTRYPOINTS);
#undef CHECK_GL_ENTRYPOINTS

	Assert(bFoundAllEntryPoints);
}

static void APIENTRY OpenGLDebugCallback(
	GLenum Source,
	GLenum Type,
	unsigned int Id,
	GLenum Severity,
	GLsizei Length,
	const char *Message,
	const void *UserParam)
{
	if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204) return;

	FString OutputMessage;

	switch (Source)
	{
	case GL_DEBUG_SOURCE_API:             OutputMessage.Append("API"); break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   OutputMessage.Append("WindowSystem"); break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: OutputMessage.Append("ShaderCompiler"); break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     OutputMessage.Append("Third Party"); break;
	case GL_DEBUG_SOURCE_APPLICATION:     OutputMessage.Append("Application"); break;
	case GL_DEBUG_SOURCE_OTHER:           OutputMessage.Append("Other"); break;
	}

	OutputMessage.Append("[");

	switch (Type)
	{
	case GL_DEBUG_TYPE_ERROR:               OutputMessage.Append("Error"); break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: OutputMessage.Append("DeprecatedBehaviour"); break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  OutputMessage.Append("UndefinedBehaviour"); break;
	case GL_DEBUG_TYPE_PORTABILITY:         OutputMessage.Append("Portability"); break;
	case GL_DEBUG_TYPE_PERFORMANCE:         OutputMessage.Append("Performance"); break;
	case GL_DEBUG_TYPE_MARKER:              OutputMessage.Append("Marker"); break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          OutputMessage.Append("PushGroup"); break;
	case GL_DEBUG_TYPE_POP_GROUP:           OutputMessage.Append("PopGroup"); break;
	case GL_DEBUG_TYPE_OTHER:               OutputMessage.Append("Other"); break;
	}

	OutputMessage.Append("]: ");

	switch (Severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         OutputMessage.Append("High"); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       OutputMessage.Append("Medium"); break;
	case GL_DEBUG_SEVERITY_LOW:          OutputMessage.Append("Low"); break;
	}

	OutputMessage.Append("- ");
	OutputMessage.Append(Message);
	
	const TCHAR *OutputMessageData = OutputMessage.GetData();
	OutputDebugString(OutputMessageData);
	OutputDebugString("\n");
}

static void 
InitializeRenderContextCoreState(FRenderContext *InOutContext)
{
	glGenVertexArrays(1, &InOutContext->VertexArray);
	glBindVertexArray(InOutContext->VertexArray);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
#if DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLDebugCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
#endif
}

void
CreateRenderContext(FRenderContext *InOutContext, HDC DeviceContext)
{
	PIXELFORMATDESCRIPTOR PixelFormatDesc = {};
	PixelFormatDesc.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
	PixelFormatDesc.nVersion     = 1;
	PixelFormatDesc.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	PixelFormatDesc.iPixelType   = PFD_TYPE_RGBA;
	PixelFormatDesc.cColorBits   = 32;
	PixelFormatDesc.cDepthBits   = 0;
	PixelFormatDesc.cStencilBits = 0;
	PixelFormatDesc.iLayerType   = PFD_MAIN_PLANE;

	int32 PixelFormat = ::ChoosePixelFormat(DeviceContext, &PixelFormatDesc);
	::SetPixelFormat(DeviceContext, PixelFormat, &PixelFormatDesc);

	int32 ExternalFlags = 0;
#if DEBUG
	ExternalFlags = WGL_CONTEXT_DEBUG_BIT_ARB;
#endif

	int32 AttribList[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 5,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | ExternalFlags,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	InOutContext->DeviceContext = DeviceContext;
	InOutContext->RenderContext = wglCreateContextAttribsARB(DeviceContext, 0, AttribList);
}

void
ReleaseRenderContext(FRenderContext *InOutContext)
{
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &InOutContext->VertexArray);
	wglDeleteContext(InOutContext->RenderContext);
}

void
MakeRenderContextCurrent(FRenderContext *InOutContext)
{
	if (InOutContext)
	{
		wglMakeCurrent(InOutContext->DeviceContext, InOutContext->RenderContext);
		InitializeRenderContextCoreState(InOutContext);
	}
	else
	{
		wglMakeCurrent(0, 0);
	}
}

void
InitPlatformOpenGL()
{
	FRenderContext RenderContext;
	FMemory::Zero(&RenderContext, sizeof(FRenderContext));

	CreateOpenGLContextWindow(&RenderContext);
	InitializeOpenGLEntryPoints(&RenderContext);
	ReleaseRenderContext(&RenderContext);
	MakeRenderContextCurrent(0);
	ReleaseOpenGLContextWindow(&RenderContext);
}