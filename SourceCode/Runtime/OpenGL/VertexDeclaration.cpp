#include "VertexDeclaration.h"
#include "OpenGL.h"

static const int32 VertexAttributeMaxIndex = 8;

void 
FVertexDeclaration::AddAttribute(const FVertexAttribute &Attribute)
{
	Assert(Attribute.AttributeIndex < VertexAttributeMaxIndex);
	Attributes.Add(Attribute);
}

void
FVertexDeclaration::AddAttributes(const TArray<FVertexAttribute> &InAttributes)
{
	Attributes.Empty();
	for (const FVertexAttribute &Attribute : InAttributes)
	{
		AddAttribute(Attribute);
	}
}

void
FVertexDeclaration::BindAttributes() const
{
	for (int32 AttributeIndex = 0; AttributeIndex < VertexAttributeMaxIndex; ++AttributeIndex)
	{
		glDisableVertexAttribArray(AttributeIndex);
	}

	for (const FVertexAttribute &Attribute : Attributes)
	{
		glEnableVertexAttribArray(Attribute.AttributeIndex);
		glVertexAttribPointer(
			Attribute.AttributeIndex,
			Attribute.AttributeCount,
			Attribute.bIsFloat ? GL_FLOAT : GL_UNSIGNED_BYTE,
			Attribute.bIsNormalized,
			Attribute.Stride,
			(const void *)Attribute.Offset
		);
	}
}