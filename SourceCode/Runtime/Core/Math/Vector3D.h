#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <CommonTypes.h>
#include <Definitions.h>

class FVector3D
{
public:
	union
	{
		struct { float X; float Y; float Z; };
		struct { float R; float G; float B; };
		struct { float S; float T; float P; };

		__m128 Register;
	};

	static CORE_API const FVector3D ZeroVector;
	static CORE_API const FVector3D OneVector;
	static CORE_API const FVector3D UpVector;
	static CORE_API const FVector3D RightVector;
	static CORE_API const FVector3D ForwardVector;

public:
	FORCEINLINE FVector3D();
	FORCEINLINE FVector3D(float X, float Y, float Z);
	FORCEINLINE FVector3D(const FVector3D &Other);
	FORCEINLINE FVector3D(const __m128 &Register);

	explicit FORCEINLINE FVector3D(float Value);
	explicit FORCEINLINE FVector3D(const FVector4D &InVectorXYZ);
	explicit FORCEINLINE FVector3D(const FVector2D &InVectorXY);
	explicit FORCEINLINE FVector3D(const FVector2D &InVectorXY, float Z);

	FORCEINLINE float GetLength() const;
	FORCEINLINE FVector3D GetNormalized() const;

	FORCEINLINE float &operator[](uint32 Index);
	FORCEINLINE float  operator[](uint32 Index) const;

	FORCEINLINE FVector3D operator-() const;
	FORCEINLINE FVector3D operator+(float Value) const;
	FORCEINLINE FVector3D operator+(const FVector3D &Other) const;
	FORCEINLINE FVector3D operator-(float Value) const;
	FORCEINLINE FVector3D operator-(const FVector3D &Other) const;
	FORCEINLINE FVector3D operator*(float Value) const;
	FORCEINLINE FVector3D operator*(const FVector3D &Other) const;
	FORCEINLINE FVector3D operator/(float Value) const;
	FORCEINLINE FVector3D operator/(const FVector3D &Other) const;

	FORCEINLINE FVector3D &operator =(float Value);
	FORCEINLINE FVector3D &operator =(const FVector3D &Other);
	FORCEINLINE FVector3D &operator+=(float Value);
	FORCEINLINE FVector3D &operator+=(const FVector3D &Other);
	FORCEINLINE FVector3D &operator-=(float Value);
	FORCEINLINE FVector3D &operator-=(const FVector3D &Other);
	FORCEINLINE FVector3D &operator*=(float Value);
	FORCEINLINE FVector3D &operator*=(const FVector3D &Other);
	FORCEINLINE FVector3D &operator/=(float Value);
	FORCEINLINE FVector3D &operator/=(const FVector3D &Other);

	FORCEINLINE bool operator==(const FVector3D &Other) const;
	FORCEINLINE bool operator!=(const FVector3D &Other) const;

	static FORCEINLINE float Dot(const FVector3D &InVectorA, const FVector3D &InVectorB);
	static FORCEINLINE FVector3D Cross(const FVector3D &InVectorA, const FVector3D &InVectorB);
};

#include "Vector2D.h"
#include "Vector4D.h"
#include "Vector3D.inl"

#endif