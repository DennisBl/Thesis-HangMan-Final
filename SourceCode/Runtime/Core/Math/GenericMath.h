#ifndef GENERIC_MATH_H
#define GENERIC_MATH_H

#include <CommonTypes.h>
#include <Definitions.h>

#define PI 3.14159265359

class FGenericMath
{
public:
	static FORCEINLINE float Abs(float Value)
	{
		return fabs(Value);
	}

	static FORCEINLINE float Exp(float Value)
	{
		return expf(Value);
	}

	static FORCEINLINE float Exp2(float Value)
	{
		return exp2f(Value);
	}

	static FORCEINLINE float Ceil(float Value)
	{
		return ceilf(Value);
	}

	static FORCEINLINE float Floor(float Value)
	{
		return floorf(Value);
	}

	static FORCEINLINE float Sqrt(float Value)
	{
		return sqrtf(Value);
	}

	static FORCEINLINE float InvSqrt(float Value)
	{
		return 1.0f / Sqrt(Value);
	}

	static FORCEINLINE float Fmod(float X, float Y)
	{
		return fmodf(X, Y);
	}

	static FORCEINLINE float Sin(float Value)
	{
		return sinf(Value);
	}

	static FORCEINLINE float Asin(float Value)
	{
		return asinf(Value);
	}

	static FORCEINLINE float Cos(float Value)
	{
		return cosf(Value);
	}

	static FORCEINLINE float Acos(float Value)
	{
		return acos(Value);
	}

	static FORCEINLINE float Tan(float Value)
	{
		return tanf(Value);
	}

	static FORCEINLINE float Atan(float Value)
	{
		return atanf(Value);
	}

	static FORCEINLINE float Atan2(float X, float Y)
	{
		return atan2f(X, Y);
	}

	static FORCEINLINE float Pow(float A, float B)
	{
		return powf(A, B);
	}

	static FORCEINLINE float Log(float A)
	{
		return log(A);
	}

	static FORCEINLINE float Log2(float A)
	{
		return log2(A);
	}

	static FORCEINLINE float Min(float A, float B)
	{
		return (A > B) ? B : A;
	}

	static FORCEINLINE float Max(float A, float B)
	{
		return (B > A) ? B : A;
	}
};

#endif