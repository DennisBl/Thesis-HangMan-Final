#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <chrono>
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include <stdint.h>
#include <typeinfo>
#include <smmintrin.h>

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef char TCHAR;

class FString;
class FArrayAllocator;
class FSparseArrayAllocator;
class FGenericSetKeyScript;

template<
	uint32 AverageElementCountPerHashBucket = 2,
	uint32 BaseHashBucketCount              = 8,
	uint32 MinHashElementCount              = 4
>
class TSetAllocator;

class FColor32;
class FGenericMath;
class FUtilityMath;
class FMath;
class FIntPoint;
class FIntRect;
class FMatrix;
class FVector2D;
class FVector3D;
class FVector4D;
class FRotator;
class FPerspectiveMatrix;
class FOrthographicMatrix;
class FTranslationMatrix;
class FRotationMatrix;
class FScaleMatrix;
class FViewRotationMatrix;

class FGenericMemory;
class FUtilityMemory;
class FMemory;
class FAllocatorInterface;
class FInlineAllocator;
class FStackAllocator;
class FFixedAllocator;
class FHeapAllocator;

template <class FirstType, class SecondType> class TPair;
template <class ElementType, class AllocatorType = FArrayAllocator> class TArray;
template <class ElementType, class KeyScript = FGenericSetKeyScript, class KeyAllocator = TSetAllocator<>> class TSet;
template <class KeyType, class ElementType> class TMap;
template <class ElementType> class TOptional;

template <class Type>
bool IsEnum()
{
    return __is_enum(Type);
}

template <typename Type>
struct TIsArithmetic
{
    enum { Value = false };
};

template <> struct TIsArithmetic<float>  { enum { Value = true }; };
template <> struct TIsArithmetic<double> { enum { Value = true }; };
template <> struct TIsArithmetic<uint8>  { enum { Value = true }; };
template <> struct TIsArithmetic<uint16> { enum { Value = true }; };
template <> struct TIsArithmetic<uint32> { enum { Value = true }; };
template <> struct TIsArithmetic<uint64> { enum { Value = true }; };
template <> struct TIsArithmetic<int8>   { enum { Value = true }; };
template <> struct TIsArithmetic<int16>  { enum { Value = true }; };
template <> struct TIsArithmetic<int32>  { enum { Value = true }; };
template <> struct TIsArithmetic<int64>  { enum { Value = true }; };
template <> struct TIsArithmetic<bool>   { enum { Value = true }; };
template <> struct TIsArithmetic<TCHAR>  { enum { Value = true }; };

template <class Type>
bool IsArithmetic()
{
    return TIsArithmetic<Type>::Value;
}

template <typename Type>
struct TIsPointer
{
    enum { Value = false };
};

template <typename Type>
struct TIsPointer<Type *>
{ 
    enum { Value = true }; 
};

template <class Type>
bool IsPointer()
{
    return TIsPointer<Type>::Value;
}

template <class Type>
bool IsZeroConstructType()
{
    return IsEnum<Type>() || IsArithmetic<Type>() || IsPointer<Type>();
}

#endif