#ifndef INT_POINT_H
#define INT_POINT_H

#include "Math.h"
#include "Vector2D.h"

class FIntPoint
{
public:
	int32 X;
	int32 Y;

public:
	FORCEINLINE FIntPoint();
	FORCEINLINE FIntPoint(int32 X, int32 Y);
	FORCEINLINE FIntPoint(const FIntPoint &Other);
	FORCEINLINE FIntPoint(const FVector2D &Other);

	explicit FORCEINLINE FIntPoint(int32 Value);

	FORCEINLINE FIntPoint &Clamp(const FIntPoint &InPoint);
	FORCEINLINE bool InsideRect(const FIntRect &InRect) const;
	FORCEINLINE FVector2D ToVector2D() const;

	FORCEINLINE FIntPoint operator+(float Value) const;
	FORCEINLINE FIntPoint operator+(const FIntPoint &Other) const;
	FORCEINLINE FIntPoint operator+(const FVector2D &Other) const;
	FORCEINLINE FIntPoint operator-(float Value) const;
	FORCEINLINE FIntPoint operator-(const FIntPoint &Other) const;
	FORCEINLINE FIntPoint operator-(const FVector2D &Other) const;
	FORCEINLINE FIntPoint operator*(float Value) const;
	FORCEINLINE FIntPoint operator*(const FIntPoint &Other) const;
	FORCEINLINE FIntPoint operator*(const FVector2D &Other) const;
	FORCEINLINE FIntPoint operator/(float Value) const;
	FORCEINLINE FIntPoint operator/(const FIntPoint &Other) const;
	FORCEINLINE FIntPoint operator/(const FVector2D &Other) const;

	FORCEINLINE FIntPoint &operator =(const FIntPoint &Other);
	FORCEINLINE FIntPoint &operator+=(float Value);
	FORCEINLINE FIntPoint &operator+=(const FIntPoint &Other);
	FORCEINLINE FIntPoint &operator+=(const FVector2D &Other);
	FORCEINLINE FIntPoint &operator-=(float Value);
	FORCEINLINE FIntPoint &operator-=(const FIntPoint &Other);
	FORCEINLINE FIntPoint &operator-=(const FVector2D &Other);
	FORCEINLINE FIntPoint &operator*=(float Value);
	FORCEINLINE FIntPoint &operator*=(const FIntPoint &Other);
	FORCEINLINE FIntPoint &operator*=(const FVector2D &Other);
	FORCEINLINE FIntPoint &operator/=(float Value);
	FORCEINLINE FIntPoint &operator/=(const FIntPoint &Other);
	FORCEINLINE FIntPoint &operator/=(const FVector2D &Other);

	FORCEINLINE bool operator==(const FIntPoint &Other) const;
	FORCEINLINE bool operator!=(const FIntPoint &Other) const;
};

#include "IntRect.h"
#include "IntPoint.inl"

#endif