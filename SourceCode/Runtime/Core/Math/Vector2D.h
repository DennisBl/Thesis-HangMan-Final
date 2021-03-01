#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <CommonTypes.h>
#include <Definitions.h>

class FVector2D
{
public:
	union
	{
		struct { float X; float Y; };
		struct { float R; float G; };
		struct { float S; float T; };
	};

public:
	FORCEINLINE FVector2D();
	FORCEINLINE FVector2D(const FVector2D &Other);
	FORCEINLINE FVector2D(float X, float Y);

	explicit FORCEINLINE FVector2D(float Value);
	explicit FORCEINLINE FVector2D(const FVector3D &Other);
	explicit FORCEINLINE FVector2D(const FVector4D &Other);

	FORCEINLINE float &operator[](uint32 Index);
	FORCEINLINE float  operator[](uint32 Index) const;

	FORCEINLINE FVector2D operator-() const;
	FORCEINLINE FVector2D operator+(float Value) const;
	FORCEINLINE FVector2D operator+(const FVector2D &Other) const;
	FORCEINLINE FVector2D operator-(float Value) const;
	FORCEINLINE FVector2D operator-(const FVector2D &Other) const;
	FORCEINLINE FVector2D operator*(float Value) const;
	FORCEINLINE FVector2D operator*(const FVector2D &Other) const;
	FORCEINLINE FVector2D operator/(float Value) const;
	FORCEINLINE FVector2D operator/(const FVector2D &Other) const;

	FORCEINLINE FVector2D &operator =(float Value);
	FORCEINLINE FVector2D &operator =(const FVector2D &Other);
	FORCEINLINE FVector2D &operator+=(float Value);
	FORCEINLINE FVector2D &operator+=(const FVector2D &Other);
	FORCEINLINE FVector2D &operator-=(float Value);
	FORCEINLINE FVector2D &operator-=(const FVector2D &Other);
	FORCEINLINE FVector2D &operator*=(float Value);
	FORCEINLINE FVector2D &operator*=(const FVector2D &Other);
	FORCEINLINE FVector2D &operator/=(float Value);
	FORCEINLINE FVector2D &operator/=(const FVector2D &Other);

	FORCEINLINE bool operator==(const FVector2D &Other) const;
	FORCEINLINE bool operator!=(const FVector2D &Other) const;
};

#include "Vector3D.h"
#include "Vector4D.h"
#include "Vector2D.inl"

#endif