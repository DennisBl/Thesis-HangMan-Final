#include "Math.h"

FORCEINLINE 
FRotator::FRotator()
{ }

FORCEINLINE 
FRotator::FRotator(float Pitch, float Yaw, float Roll)
	: Pitch(Pitch)
	, Yaw(Yaw)
	, Roll(Roll)
{ }

FORCEINLINE bool 
FRotator::operator==(const FRotator &Other) const
{
	return Pitch == Other.Pitch &&
		   Yaw   == Other.Yaw   &&
		   Roll  == Other.Roll;
}

FORCEINLINE bool 
FRotator::operator!=(const FRotator &Other) const
{
	return !(*this == Other);
}

FORCEINLINE 
FTranslationMatrix::FTranslationMatrix(const FVector3D &Origin)
	: FMatrix(
		FVector4D(1.0f, 0.0f, 0.0f, 0.0f),
		FVector4D(0.0f, 1.0f, 0.0f, 0.0f),
		FVector4D(0.0f, 0.0f, 1.0f, 0.0f),
		FVector4D(Origin.X, Origin.Y, Origin.Z, 1.0f))
{ }

FORCEINLINE 
FRotationMatrix::FRotationMatrix(const FVector3D &Rotation)
	: FMatrix(
		FMatrix(
			FVector4D(1.0f, 0.0f, 0.0f, 0.0f),
			FVector4D(0.0f, +FMath::Cos(Rotation.X), +FMath::Sin(Rotation.X), 0.0f),
			FVector4D(0.0f, -FMath::Sin(Rotation.X), +FMath::Cos(Rotation.X), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix(
			FVector4D(+FMath::Cos(Rotation.Y), 0.0f, -FMath::Sin(Rotation.Y), 0.0f),
			FVector4D(0.0f, 1.0f, 0.0f, 0.0f),
			FVector4D(+FMath::Sin(Rotation.Y), 0.0f, +FMath::Cos(Rotation.Y), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix(
			FVector4D(+FMath::Cos(Rotation.Z), +FMath::Sin(Rotation.Z), 0.0f, 0.0f),
			FVector4D(-FMath::Sin(Rotation.Z), +FMath::Cos(Rotation.Z), 0.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 1.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)))
{ }

FORCEINLINE 
FRotationMatrix::FRotationMatrix(float Pitch, float Yaw, float Roll)
	: FMatrix(
		FMatrix(
			FVector4D(1.0f, 0.0f, 0.0f, 0.0f),
			FVector4D(0.0f, +FMath::Cos(Pitch * PI / 180.f), +FMath::Sin(Pitch * PI / 180.f), 0.0f),
			FVector4D(0.0f, -FMath::Sin(Pitch * PI / 180.f), +FMath::Cos(Pitch * PI / 180.f), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix(
			FVector4D(+FMath::Cos(Yaw * PI / 180.f), 0.0f, -FMath::Sin(Yaw * PI / 180.f), 0.0f),
			FVector4D(0.0f, 1.0f, 0.0f, 0.0f),
			FVector4D(+FMath::Sin(Yaw * PI / 180.f), 0.0f, +FMath::Cos(Yaw * PI / 180.f), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix(
			FVector4D(+FMath::Cos(Roll * PI / 180.f), +FMath::Sin(Roll * PI / 180.f), 0.0f, 0.0f),
			FVector4D(-FMath::Sin(Roll * PI / 180.f), +FMath::Cos(Roll * PI / 180.f), 0.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 1.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)))
{ }

FORCEINLINE 
FRotationMatrix::FRotationMatrix(const FRotator &Rotator)
	: FMatrix(
		FMatrix(
			FVector4D(1.0f, 0.0f, 0.0f, 0.0f),
			FVector4D(0.0f, +FMath::Cos(Rotator.Pitch * PI / 180.f), +FMath::Sin(Rotator.Pitch * PI / 180.f), 0.0f),
			FVector4D(0.0f, -FMath::Sin(Rotator.Pitch * PI / 180.f), +FMath::Cos(Rotator.Pitch * PI / 180.f), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix(
			FVector4D(+FMath::Cos(Rotator.Yaw * PI / 180.f), 0.0f, -FMath::Sin(Rotator.Yaw * PI / 180.f), 0.0f),
			FVector4D(0.0f, 1.0f, 0.0f, 0.0f),
			FVector4D(+FMath::Sin(Rotator.Yaw * PI / 180.f), 0.0f, +FMath::Cos(Rotator.Yaw * PI / 180.f), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix(
			FVector4D(+FMath::Cos(Rotator.Roll * PI / 180.f), +FMath::Sin(Rotator.Roll * PI / 180.f), 0.0f, 0.0f),
			FVector4D(-FMath::Sin(Rotator.Roll * PI / 180.f), +FMath::Cos(Rotator.Roll * PI / 180.f), 0.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 1.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)))
{ }

FORCEINLINE
FInverseRotationMatrix::FInverseRotationMatrix(float InPitch, float InYaw, float InRoll)
	: FMatrix(
		FMatrix( // Yaw
			FVector4D(+FMath::Cos(InYaw * PI / 180.f), -FMath::Sin(InYaw * PI / 180.f), 0.0f, 0.0f),
			FVector4D(+FMath::Sin(InYaw * PI / 180.f), +FMath::Cos(InYaw * PI / 180.f), 0.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 1.0f, 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix( // Pitch
			FVector4D(+FMath::Cos(InPitch * PI / 180.f), 0.0f, -FMath::Sin(InPitch * PI / 180.f), 0.0f),
			FVector4D(0.0f, 1.0f, 0.0f, 0.0f),
			FVector4D(+FMath::Sin(InPitch * PI / 180.f), 0.0f, +FMath::Cos(InPitch * PI / 180.f), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)) *
		FMatrix( // Roll
			FVector4D(1.0f, 0.0f, 0.0f, 0.0f),
			FVector4D(0.0f, +FMath::Cos(InRoll * PI / 180.f), +FMath::Sin(InRoll * PI / 180.f), 0.0f),
			FVector4D(0.0f, -FMath::Sin(InRoll * PI / 180.f), +FMath::Cos(InRoll * PI / 180.f), 0.0f),
			FVector4D(0.0f, 0.0f, 0.0f, 1.0f)))
{ }

FORCEINLINE 
FScaleMatrix::FScaleMatrix(float Scale)
	: FMatrix(
		FVector4D(Scale, 0.0f,  0.0f,  0.0f),
		FVector4D(0.0f,  Scale, 0.0f,  0.0f),
		FVector4D(0.0f,  0.0f,  Scale, 0.0f),
		FVector4D(0.0f,  0.0f,  0.0f,  1.0f))
{ }

FORCEINLINE 
FScaleMatrix::FScaleMatrix(const FVector3D &Scale)
	: FMatrix(
		FVector4D(Scale.X, 0.0f,    0.0f,    0.0f),
		FVector4D(0.0f,    Scale.Y, 0.0f,    0.0f),
		FVector4D(0.0f,    0.0f,    Scale.Z, 0.0f),
		FVector4D(0.0f,    0.0f,    0.0f,	 1.0f))
{ }

FORCEINLINE
FPerspectiveMatrix::FPerspectiveMatrix(float FoV, float AspectRatio)
	: FMatrix(
		FVector4D(1.0f / (FMath::Tan(FoV / 2.0f) * AspectRatio), 0.0f,						    0.0f, 0.0f),
		FVector4D(0.0f,										     1.0f / FMath::Tan(FoV / 2.0f), 0.0f, 0.0f),
		FVector4D(0.0f,										     0.0f,						    1.0f, 1.0f),
		FVector4D(0.0f,									         0.0f,						   -1.0f, 0.0f))
{ }

FORCEINLINE
FPerspectiveMatrix::FPerspectiveMatrix(float FoV, float AspectRatio, float ZNear, float ZFar)
	: FMatrix(
		FVector4D(1.0f / (FMath::Tan(FoV / 2.0f) * AspectRatio), 0.0f,						    0.0f,						   0.0f),
		FVector4D(0.0f,										     1.0f / FMath::Tan(FoV / 2.0f), 0.0f,					       0.0f),
		FVector4D(0.0f,									         0.0f,						    ZNear / (ZNear - ZFar),		   1.0f),
		FVector4D(0.0f,								             0.0f,					       -ZNear * ZFar / (ZNear - ZFar), 0.0f))
{ }

FOrthographicMatrix::FOrthographicMatrix(float SizeX, float SizeY)
	: FMatrix(
		FVector4D(SizeX ? 2.0 / SizeX : 1.0, 0.0,                       0.0, 0.0),
		FVector4D( 0.0,                      SizeY ? 2.0 / SizeY : 1.0, 0.0, 0.0),
		FVector4D( 0.0,                      0.0,                       1.0, 0.0),
		FVector4D(-1.0,                     -1.0,                       0.0, 1.0))
{ }

FORCEINLINE
FOrthographicMatrix::FOrthographicMatrix(float SizeX, float SizeY, float ZNear, float ZFar)
	: FMatrix(
		FVector4D(SizeX ? 2.0 / SizeX : 1, 0.0,                       0.0,                                          0.0),
		FVector4D( 0.0,                    SizeY ? 2.0 / SizeY : 1.0, 0.0,	                                        0.0),
		FVector4D( 0.0,                    0.0,			             (ZFar - ZNear) ? 1.0 / (ZFar - ZNear)   : 1.0, 0.0),
		FVector4D(-1.0,                   -1.0,			             (ZFar - ZNear) ? ZNear / (ZNear - ZFar) : 1.0, 1.0))
{ }