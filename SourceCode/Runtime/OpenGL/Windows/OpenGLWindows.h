#ifndef OPENGL_WINDOWS_H
#define OPENGL_WINDOWS_H

#include "EntryPoints.h"
#include <Platform.h>

struct FRenderContext
{
	HWND WindowHandle;
	HDC DeviceContext;
	HGLRC RenderContext;

	uint32 VertexArray;
};

void CreateRenderContext(FRenderContext *InOutContext, HDC DeviceContext);
void ReleaseRenderContext(FRenderContext *InOutContext);
void MakeRenderContextCurrent(FRenderContext *InOutContext);

void InitPlatformOpenGL();

#endif