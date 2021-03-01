#include "PixelShader.h"
#include "OpenGL.h"

FPixelShader::FPixelShader(const FString &InSourceCode)
	: ResourceId(0)
{
	ResourceId = glCreateShader(GL_FRAGMENT_SHADER);

	const TCHAR *SourceCode = InSourceCode.GetData();
	int32 SourceCodeSize = InSourceCode.GetLength();

	glShaderSource(ResourceId, 1, &SourceCode, &SourceCodeSize);
	glCompileShader(ResourceId);

	int32 Success = 0;
	glGetShaderiv(ResourceId, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		TCHAR CompileLog[4096];
		glGetShaderInfoLog(ResourceId, 4096, 0, CompileLog);
		OutputDebugString(CompileLog);
	};
}

FPixelShader::~FPixelShader()
{
	glDeleteShader(ResourceId);
}