#ifndef OPENGL_H
#define OPENGL_H

#include <CoreMinimal.h>

#if PLATFORM_WINDOWS
#include "Windows/OpenGLWindows.h"
#elif PLATFORM_LINUX
#elif PLATFORM_IOS
#elif PLATFORM_ANDROID
#endif

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture2D.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "PipelineState.h"
#include "VertexDeclaration.h"

class FOpenGL
{
public:
	FORCEINLINE static void Present(FWindow *Window)
	{
		HDC DeviceContext = Window->GetDeviceContext();
		SwapBuffers(DeviceContext);
	}

	FORCEINLINE static void Clear(const FColor32 &Color)
	{
		FVector4D NormalizedColor;
		NormalizedColor.R = static_cast<float>(Color.R) / 255.0f;
		NormalizedColor.G = static_cast<float>(Color.G) / 255.0f;
		NormalizedColor.B = static_cast<float>(Color.B) / 255.0f;
		NormalizedColor.A = static_cast<float>(Color.A) / 255.0f;

		glClearColor(NormalizedColor.R, NormalizedColor.G, NormalizedColor.B, NormalizedColor.A);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	FORCEINLINE static void Draw(uint32 Count)
	{
		glDrawArrays(GL_TRIANGLES, 0, Count);
	}

	FORCEINLINE static void DrawIndexed(uint32 Count, uint32 FirstIndex, uint32 BaseVertex)
	{
		glDrawElementsBaseVertex(GL_TRIANGLES, Count, GL_UNSIGNED_INT, (const void *)FirstIndex, BaseVertex);
	}
};

#endif