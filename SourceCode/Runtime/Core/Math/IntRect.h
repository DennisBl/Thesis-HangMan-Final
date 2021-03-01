#ifndef INT_RECT_H
#define INT_RECT_H

#include "Math.h"
#include "Vector4D.h"

class FIntRect
{
public:
	FIntPoint Min;
	FIntPoint Max;

public:
	FORCEINLINE FIntRect();
	FORCEINLINE FIntRect(int32 MinX, int32 MinY, int32 MaxX, int32 MaxY);
	FORCEINLINE FIntRect(const FIntRect &Other);
	FORCEINLINE FIntRect(const FVector4D &Other);

	explicit FORCEINLINE FIntRect(float Value);
	explicit FORCEINLINE FIntRect(const FVector2D &Min, const FVector2D &Max);
	explicit FORCEINLINE FIntRect(const FIntPoint &Min, const FIntPoint &Max);

	FORCEINLINE FIntRect &Clamp(const FIntPoint &InMin, const FIntPoint &InMax);
	FORCEINLINE bool InsideRect(const FIntRect &InRect) const;
	FORCEINLINE FVector4D ToVector4D() const;

	FORCEINLINE int32 GetOriginX() const;
	FORCEINLINE int32 GetOriginY() const;
	FORCEINLINE FIntPoint GetOrigin() const;

	FORCEINLINE int32 GetSizeX() const;
	FORCEINLINE int32 GetSizeY() const;
	FORCEINLINE FIntPoint GetSize() const;

	FORCEINLINE FIntRect operator+(float Value) const;
	FORCEINLINE FIntRect operator+(const FIntRect &Other) const;
	FORCEINLINE FIntRect operator+(const FVector4D &Other) const;
	FORCEINLINE FIntRect operator-(float Value) const;
	FORCEINLINE FIntRect operator-(const FIntRect &Other) const;
	FORCEINLINE FIntRect operator-(const FVector4D &Other) const;
	FORCEINLINE FIntRect operator*(float Value) const;
	FORCEINLINE FIntRect operator*(const FIntRect &Other) const;
	FORCEINLINE FIntRect operator*(const FVector4D &Other) const;
	FORCEINLINE FIntRect operator/(float Value) const;
	FORCEINLINE FIntRect operator/(const FIntRect &Other) const;
	FORCEINLINE FIntRect operator/(const FVector4D &Other) const;

	FORCEINLINE FIntRect &operator =(const FIntRect &Other);
	FORCEINLINE FIntRect &operator+=(float Value);
	FORCEINLINE FIntRect &operator+=(const FIntRect &Other);
	FORCEINLINE FIntRect &operator+=(const FVector4D &Other);
	FORCEINLINE FIntRect &operator-=(float Value);
	FORCEINLINE FIntRect &operator-=(const FIntRect &Other);
	FORCEINLINE FIntRect &operator-=(const FVector4D &Other);
	FORCEINLINE FIntRect &operator*=(float Value);
	FORCEINLINE FIntRect &operator*=(const FIntRect &Other);
	FORCEINLINE FIntRect &operator*=(const FVector4D &Other);
	FORCEINLINE FIntRect &operator/=(float Value);
	FORCEINLINE FIntRect &operator/=(const FIntRect &Other);
	FORCEINLINE FIntRect &operator/=(const FVector4D &Other);

	FORCEINLINE bool operator==(const FIntRect &Other) const;
	FORCEINLINE bool operator!=(const FIntRect &Other) const;
};

#include "IntPoint.h"
#include "IntRect.inl"

#endif