#ifndef MATRIX_H
#define MATRIX_H

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

class FMatrix
{
public:
	FVector4D Planes[4];

	static CORE_API const FMatrix Identity;

public:
	FORCEINLINE FMatrix();
	FORCEINLINE FMatrix(float Value);
	FORCEINLINE FMatrix(const FMatrix &Other);
	FORCEINLINE FMatrix(const FVector4D &Vector0, const FVector4D &Vector1, const FVector4D &Vector2, const FVector4D &Vector3);

	FORCEINLINE FMatrix Translate(const FVector3D &InTranslation);
	FORCEINLINE FMatrix Scale(const FVector3D &InScale);

	

	FORCEINLINE FMatrix GetInversed() const;
	FORCEINLINE FMatrix GetTransposed() const;

	FORCEINLINE FVector4D &operator [](uint32 Index);
	FORCEINLINE const FVector4D &operator [](uint32 Index) const;

	FORCEINLINE FMatrix operator +(float Value) const;
	FORCEINLINE FMatrix operator +(const FMatrix &Other) const;
	FORCEINLINE FMatrix operator *(float Value) const;
	FORCEINLINE FMatrix operator *(const FMatrix &Other) const;

	FORCEINLINE FMatrix &operator  =(const FMatrix &Other);
	FORCEINLINE FMatrix &operator +=(float Value);
	FORCEINLINE FMatrix &operator +=(const FMatrix &Other);
	FORCEINLINE FMatrix &operator *=(float Value);
	FORCEINLINE FMatrix &operator *=(const FMatrix &Other);

	FORCEINLINE bool operator ==(const FMatrix &Other) const;
	FORCEINLINE bool operator !=(const FMatrix &Other) const;
};

#include "Matrix.inl"

#endif