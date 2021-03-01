#include "PipelineState.h"
#include "OpenGL.h"

FPipelineState::FPipelineState(const FPipelineStateInitializer &Initializer)
	: ResourceId(0)
{
	ResourceId = glCreateProgram();

	const FVertexShader *VertexShader = Initializer.VertexShader;
	const FPixelShader *PixelShader = Initializer.PixelShader;

	const uint32 VertexShaderResourceId = VertexShader->GetResourceId();
	const uint32 PixelShaderResourceId = PixelShader->GetResourceId();

	glAttachShader(ResourceId, VertexShaderResourceId);
	glAttachShader(ResourceId, PixelShaderResourceId);
	glLinkProgram(ResourceId);

	int32 Success = 0;
	glGetProgramiv(ResourceId, GL_LINK_STATUS, &Success);
	if (!Success)
	{
		TCHAR LinkageLog[4096];
		glGetProgramInfoLog(ResourceId, 4096, 0, LinkageLog);
		OutputDebugString(LinkageLog);
	}
}

FPipelineState::~FPipelineState()
{
	glDeleteProgram(ResourceId);
}

void
FPipelineState::Bind()
{
	glUseProgram(ResourceId);
}

void
FPipelineState::SetUniformMatrix(const TCHAR *UniformName, FMatrix &Matrix)
{
	int32 LocationId = glGetUniformLocation(ResourceId, UniformName);
	glUniformMatrix4fv(LocationId, 1, false, &Matrix[0][0]);
}