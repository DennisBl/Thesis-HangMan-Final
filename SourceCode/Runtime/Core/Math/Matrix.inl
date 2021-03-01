#include "Transform.h"

FORCEINLINE
FMatrix::FMatrix()
{
	Planes[0] = FVector4D(1, 0, 0, 0);
	Planes[1] = FVector4D(0, 1, 0, 0);
	Planes[2] = FVector4D(0, 0, 1, 0);
	Planes[3] = FVector4D(0, 0, 0, 1);
}

FORCEINLINE
FMatrix::FMatrix(float Value)
{
	Planes[0] = FVector4D(Value, 0, 0, 0);
	Planes[1] = FVector4D(0, Value, 0, 0);
	Planes[2] = FVector4D(0, 0, Value, 0);
	Planes[3] = FVector4D(0, 0, 0, Value);
}

FORCEINLINE
FMatrix::FMatrix(const FMatrix &Other)
{
	Planes[0] = Other[0];
	Planes[1] = Other[1];
	Planes[2] = Other[2];
	Planes[3] = Other[3];
}

FORCEINLINE
FMatrix::FMatrix(const FVector4D &Vector0, const FVector4D &Vector1, const FVector4D &Vector2, const FVector4D &Vector3)
{
	Planes[0] = Vector0;
	Planes[1] = Vector1;
	Planes[2] = Vector2;
	Planes[3] = Vector3;
}

FORCEINLINE FMatrix
FMatrix::Translate(const FVector3D &InTranslation)
{
	FMatrix &Result = *this;
	Result *= FTranslationMatrix(InTranslation);
	return Result;
}

FORCEINLINE FMatrix
FMatrix::Scale(const FVector3D &InScale)
{
	FMatrix &Result = *this;
	Result *= FScaleMatrix(InScale);
	return Result;
}

FORCEINLINE FMatrix 
FMatrix::GetInversed() const
{
	float Coef00 = Planes[2][2] * Planes[3][3] - Planes[3][2] * Planes[2][3];
	float Coef02 = Planes[1][2] * Planes[3][3] - Planes[3][2] * Planes[1][3];
	float Coef03 = Planes[1][2] * Planes[2][3] - Planes[2][2] * Planes[1][3];

	float Coef04 = Planes[2][1] * Planes[3][3] - Planes[3][1] * Planes[2][3];
	float Coef06 = Planes[1][1] * Planes[3][3] - Planes[3][1] * Planes[1][3];
	float Coef07 = Planes[1][1] * Planes[2][3] - Planes[2][1] * Planes[1][3];

	float Coef08 = Planes[2][1] * Planes[3][2] - Planes[3][1] * Planes[2][2];
	float Coef10 = Planes[1][1] * Planes[3][2] - Planes[3][1] * Planes[1][2];
	float Coef11 = Planes[1][1] * Planes[2][2] - Planes[2][1] * Planes[1][2];

	float Coef12 = Planes[2][0] * Planes[3][3] - Planes[3][0] * Planes[2][3];
	float Coef14 = Planes[1][0] * Planes[3][3] - Planes[3][0] * Planes[1][3];
	float Coef15 = Planes[1][0] * Planes[2][3] - Planes[2][0] * Planes[1][3];

	float Coef16 = Planes[2][0] * Planes[3][2] - Planes[3][0] * Planes[2][2];
	float Coef18 = Planes[1][0] * Planes[3][2] - Planes[3][0] * Planes[1][2];
	float Coef19 = Planes[1][0] * Planes[2][2] - Planes[2][0] * Planes[1][2];

	float Coef20 = Planes[2][0] * Planes[3][1] - Planes[3][0] * Planes[2][1];
	float Coef22 = Planes[1][0] * Planes[3][1] - Planes[3][0] * Planes[1][1];
	float Coef23 = Planes[1][0] * Planes[2][1] - Planes[2][0] * Planes[1][1];

	FVector4D Fac0(Coef00, Coef00, Coef02, Coef03);
	FVector4D Fac1(Coef04, Coef04, Coef06, Coef07);
	FVector4D Fac2(Coef08, Coef08, Coef10, Coef11);
	FVector4D Fac3(Coef12, Coef12, Coef14, Coef15);
	FVector4D Fac4(Coef16, Coef16, Coef18, Coef19);
	FVector4D Fac5(Coef20, Coef20, Coef22, Coef23);

	FVector4D Vec0(Planes[1][0], Planes[0][0], Planes[0][0], Planes[0][0]);
	FVector4D Vec1(Planes[1][1], Planes[0][1], Planes[0][1], Planes[0][1]);
	FVector4D float2(Planes[1][2], Planes[0][2], Planes[0][2], Planes[0][2]);
	FVector4D float3(Planes[1][3], Planes[0][3], Planes[0][3], Planes[0][3]);

	FVector4D Inv0(Vec1 * Fac0 - float2 * Fac1 + float3 * Fac2);
	FVector4D Inv1(Vec0 * Fac0 - float2 * Fac3 + float3 * Fac4);
	FVector4D Inv2(Vec0 * Fac1 - Vec1 * Fac3 + float3 * Fac5);
	FVector4D Inv3(Vec0 * Fac2 - Vec1 * Fac4 + float2 * Fac5);

	FVector4D SignA(+1, -1, +1, -1);
	FVector4D SignB(-1, +1, -1, +1);
	FMatrix Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

	FVector4D Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);
	FVector4D Dot0(Planes[0] * Row0);

	float Dot1 = (Dot0.X + Dot0.Y) + (Dot0.Z + Dot0.W);
	float OneOverDeterminant = 1.0 / Dot1;

	return Inverse * OneOverDeterminant;
}

FORCEINLINE FMatrix 
FMatrix::GetTransposed() const
{
	FMatrix Result;
	Result[0][0] = Planes[0][0];
	Result[0][1] = Planes[1][0];
	Result[0][2] = Planes[2][0];
	Result[0][3] = Planes[3][0];

	Result[1][0] = Planes[0][1];
	Result[1][1] = Planes[1][1];
	Result[1][2] = Planes[2][1];
	Result[1][3] = Planes[3][1];

	Result[2][0] = Planes[0][2];
	Result[2][1] = Planes[1][2];
	Result[2][2] = Planes[2][2];
	Result[2][3] = Planes[3][2];

	Result[3][0] = Planes[0][3];
	Result[3][1] = Planes[1][3];
	Result[3][2] = Planes[2][3];
	Result[3][3] = Planes[3][3];
	return Result;
}

FORCEINLINE FVector4D &
FMatrix::operator [](uint32 Index)
{
	Assert(Index < 4);
	return Planes[Index];
}

FORCEINLINE const FVector4D &
FMatrix::operator [](uint32 Index) const
{
	Assert(Index < 4);
	return Planes[Index];
}

FORCEINLINE FMatrix &
FMatrix::operator =(const FMatrix &Matrix)
{
	Planes[0] = Matrix[0];
	Planes[1] = Matrix[1];
	Planes[2] = Matrix[2];
	Planes[3] = Matrix[3];
	return *this;
}

FORCEINLINE FMatrix
FMatrix::operator +(const FMatrix &Other) const
{
	FMatrix Result;
	Result[0] = Planes[0] + Other.Planes[0];
	Result[1] = Planes[1] + Other.Planes[1];
	Result[2] = Planes[2] + Other.Planes[2];
	Result[3] = Planes[3] + Other.Planes[3];
	return Result;
}

FORCEINLINE FMatrix
FMatrix::operator +(float Value) const
{
	FMatrix Result;
	Result[0] = Planes[0] + Value;
	Result[1] = Planes[1] + Value;
	Result[2] = Planes[2] + Value;
	Result[3] = Planes[3] + Value;
	return Result;
}

FORCEINLINE FMatrix
FMatrix::operator *(const FMatrix &Other) const
{
	FVector4D const SrcA0 = Planes[0];
	FVector4D const SrcA1 = Planes[1];
	FVector4D const SrcA2 = Planes[2];
	FVector4D const SrcA3 = Planes[3];

	FVector4D const SrcB0 = Other[0];
	FVector4D const SrcB1 = Other[1];
	FVector4D const SrcB2 = Other[2];
	FVector4D const SrcB3 = Other[3];

	FMatrix Result;
	Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
	Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
	Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
	Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
	return Result;
}

FORCEINLINE FMatrix
FMatrix::operator *(float Value) const
{
	FMatrix Result;
	Result[0] = Planes[0] * Value;
	Result[1] = Planes[1] * Value;
	Result[2] = Planes[2] * Value;
	Result[3] = Planes[3] * Value;
	return Result;
}

FORCEINLINE FMatrix &
FMatrix::operator+=(const FMatrix &Matrix)
{
	Planes[0] += Matrix[0];
	Planes[1] += Matrix[1];
	Planes[2] += Matrix[2];
	Planes[3] += Matrix[3];
	return *this;
}

FORCEINLINE FMatrix &
FMatrix::operator+=(float Value)
{
	Planes[0] += Value;
	Planes[1] += Value;
	Planes[2] += Value;
	Planes[3] += Value;
	return *this;
}

FORCEINLINE FMatrix &
FMatrix::operator*=(const FMatrix &Matrix)
{
	Planes[0] *= Matrix[0];
	Planes[1] *= Matrix[1];
	Planes[2] *= Matrix[2];
	Planes[3] *= Matrix[3];
	return *this;
}

FORCEINLINE FMatrix &
FMatrix::operator*=(float Value)
{
	Planes[0] *= Value;
	Planes[1] *= Value;
	Planes[2] *= Value;
	Planes[3] *= Value;
	return *this;
}

FORCEINLINE bool
FMatrix::operator ==(const FMatrix &Other) const
{
	return (Planes[0] == Other[0]) && (Planes[1] == Other[1]) && (Planes[2] == Other[2]) && (Planes[3] == Other[3]);
}

FORCEINLINE bool
FMatrix::operator !=(const FMatrix &Other) const
{
	return !(*this == Other);
}