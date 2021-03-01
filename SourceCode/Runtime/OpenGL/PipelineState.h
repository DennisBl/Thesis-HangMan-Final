#ifndef PIPELINE_STATE_H
#define PIPELINE_STATE_H

#include "VertexShader.h"
#include "PixelShader.h"

struct FPipelineStateInitializer
{
	const FVertexShader *VertexShader;
	const FPixelShader *PixelShader;
};

class FPipelineState
{
public:
	FPipelineState(const FPipelineStateInitializer &Initializer);
	~FPipelineState();

	void Bind();

	void SetUniformMatrix(const TCHAR *UniformName, FMatrix &Matrix);

	FORCEINLINE uint32 GetResourceId() const
	{
		return ResourceId;
	}

private:
	uint32 ResourceId;
};

#endif