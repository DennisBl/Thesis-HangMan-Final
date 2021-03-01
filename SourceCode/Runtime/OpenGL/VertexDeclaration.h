#ifndef VERTEX_DECLARATION
#define VERTEX_DECLARATION

#include <CoreMinimal.h>

struct FVertexAttribute
{
	int32 AttributeIndex;
	int32 AttributeCount;
	int32 Offset;
	int32 Stride;
	int32 bIsFloat;
	int32 bIsNormalized;

	FORCEINLINE FVertexAttribute()
	{ }

	FORCEINLINE FVertexAttribute(int32 AttributeIndex, int32 AttributeCount, int32 Offset, int32 Stride, int32 bIsFloat, int32 bIsNormalized)
		: AttributeIndex(AttributeIndex)
		, AttributeCount(AttributeCount)
		, Offset(Offset)
		, Stride(Stride)
		, bIsFloat(bIsFloat)
		, bIsNormalized(bIsNormalized)
	{ }
};

class FVertexDeclaration
{
public:
	TArray<FVertexAttribute> Attributes;

public:
	void AddAttribute(const FVertexAttribute &Attribute);
	void AddAttributes(const TArray<FVertexAttribute> &InAttributes);
	void BindAttributes() const;
};

#endif