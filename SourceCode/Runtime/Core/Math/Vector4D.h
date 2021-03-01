#ifndef VECTOR_4D_H
#define VECTOR_4D_H

#include <CommonTypes.h>
#include <Definitions.h>

class FVector4D
{
public:
	union
	{
		struct { float X; float Y; float Z; float W; };
		struct { float R; float G; float B; float A; };
		struct { float S; float T; float P; float Q; };

		__m128 Register;
	};

public:
	FORCEINLINE FVector4D();
	FORCEINLINE FVector4D(float X, float Y, float Z, float W);
	FORCEINLINE FVector4D(const FVector4D &Other);
	FORCEINLINE FVector4D(const __m128 &InRegister);

	explicit FORCEINLINE FVector4D(float Value);
	explicit FORCEINLINE FVector4D(const FVector2D &InVectorXY, const FVector2D &InVectorZW);
	explicit FORCEINLINE FVector4D(const FVector2D &InVectorXY, float Z, float W);
	explicit FORCEINLINE FVector4D(const FVector3D &InVectorXYZ, float W);

	FORCEINLINE float &operator[](uint32 Index);
	FORCEINLINE float  operator[](uint32 Index) const;

	FORCEINLINE FVector4D operator-() const;
	FORCEINLINE FVector4D operator+(float Value) const;
	FORCEINLINE FVector4D operator+(const FVector4D &Other) const;
	FORCEINLINE FVector4D operator-(float Value) const;
	FORCEINLINE FVector4D operator-(const FVector4D &Other) const;
	FORCEINLINE FVector4D operator*(float Value) const;
	FORCEINLINE FVector4D operator*(const FVector4D &Other) const;
	FORCEINLINE FVector4D operator/(float Value) const;
	FORCEINLINE FVector4D operator/(const FVector4D &Other) const;

	FORCEINLINE FVector4D &operator =(float Value);
	FORCEINLINE FVector4D &operator =(const FVector4D &Other);
	FORCEINLINE FVector4D &operator+=(float Value);
	FORCEINLINE FVector4D &operator+=(const FVector4D &Other);
	FORCEINLINE FVector4D &operator-=(float Value);
	FORCEINLINE FVector4D &operator-=(const FVector4D &Other);
	FORCEINLINE FVector4D &operator*=(float Value);
	FORCEINLINE FVector4D &operator*=(const FVector4D &Other);
	FORCEINLINE FVector4D &operator/=(float Value);
	FORCEINLINE FVector4D &operator/=(const FVector4D &Other);

	FORCEINLINE bool operator==(const FVector4D &Other) const;
	FORCEINLINE bool operator!=(const FVector4D &Other) const;
};

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.inl"

#endif