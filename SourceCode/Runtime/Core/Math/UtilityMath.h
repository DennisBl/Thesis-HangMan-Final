#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include "GenericMath.h"

class FUtilityMath : public FGenericMath
{
public:
	static FORCEINLINE int32 TruncToInt(float Value)
	{
		return (int32)Value;
	}

	static FORCEINLINE float TruncToFloat(float Value)
	{
		return (float)((int32)Value);
	}

	static FORCEINLINE uint32 CeilLogTwo(uint32 Value)
	{
		return FGenericMath::Ceil(FGenericMath::Log2(Value));
	}

	static FORCEINLINE uint32 RoundUpToPowerOfTwo(uint32 Value)
	{
		return 1 << CeilLogTwo(Value);
	}

	static FORCEINLINE float Random(float Min, float Max)
	{
		return Min + (static_cast<float>(rand()) / static_cast<float>(0x7FFF / (Max - Min)));
	}

	static FORCEINLINE float Radians(float Angle)
	{
		return Angle * PI / 180.0f;
	}

	static FORCEINLINE float Degrees(float Angle)
	{
		return Angle * 180.0f / PI;
	}
};

#endif