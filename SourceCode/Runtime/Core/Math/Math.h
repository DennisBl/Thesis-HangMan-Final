#ifndef MATH_H
#define MATH_H

#include "../HAL/PlatformMath.h"

class FMath : public FPlatformMath
{
public:
	template <class Type>
	static FORCEINLINE void Swap(Type &A, Type &B)
	{
		Type Temp = A;
		A = B;
		B = Temp;
	}

	template <class Type>
	static FORCEINLINE Type Clamp(Type Value, Type Min, Type Max)
	{
		return Value < Min ? Min : Value > Max ? Max : Value;
	}

	template <class Type>
	static FORCEINLINE Type CircularClamp(Type Value, Type Min, Type Max)
	{
		return Value < Min ? Max : Value > Max ? Min : Value;
	}
};

#endif