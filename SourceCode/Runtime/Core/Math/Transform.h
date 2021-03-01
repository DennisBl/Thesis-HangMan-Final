#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix.h"

class FRotator
{
public:
	float Pitch;
	float Yaw;
	float Roll;

public:
	FORCEINLINE FRotator();
	FORCEINLINE FRotator(float Pitch, float Yaw, float Roll);

	FORCEINLINE bool operator==(const FRotator &Other) const;
	FORCEINLINE bool operator!=(const FRotator &Other) const;
};

class FTranslationMatrix : public FMatrix
{
public:
	FORCEINLINE FTranslationMatrix(const FVector3D &Origin);
};

class FRotationMatrix : public FMatrix
{
public:
	FORCEINLINE FRotationMatrix(const FVector3D &Rotation);
	FORCEINLINE FRotationMatrix(float Pitch, float Yaw, float Roll);
	FORCEINLINE FRotationMatrix(const FRotator &Rotator);
};

class FInverseRotationMatrix : public FMatrix
{
public:
	FORCEINLINE FInverseRotationMatrix(float Pitch, float Yaw, float Roll);
};

class FScaleMatrix : public FMatrix
{
public:
	FORCEINLINE FScaleMatrix(float Scale);
	FORCEINLINE FScaleMatrix(const FVector3D &Scale);
};

class FPerspectiveMatrix : public FMatrix
{
public:
	FORCEINLINE FPerspectiveMatrix(float FoV, float AspectRatio);
	FORCEINLINE FPerspectiveMatrix(float FoV, float AspectRatio, float ZNear, float ZFar);
};

class FOrthographicMatrix : public FMatrix
{
public:
	FORCEINLINE FOrthographicMatrix(float SizeX, float SizeY);
	FORCEINLINE FOrthographicMatrix(float SizeX, float SizeY, float ZNear, float ZFar);
};

#include "Transform.inl"

#endif