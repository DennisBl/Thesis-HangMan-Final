#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#if _WIN32
#define PLATFORM_WINDOWS  1
#define PLATFORM_DESKTOP  1
#elif __linux__
#define PLATFORM_LINUX    1
#define PLATFORM_DESKTOP  1
#elif __APPLE__
#define PLATFORM_IOS      1
#define PLATFORM_MOBILE   1
#elif __ANDROID__
#define PLATFORM_ANDROID  1
#define PLATFORM_MOBILE   1
#else
#error "Platform is not recognized or supported. Supported Platforms are: Windows, iOS, Linux, Android."
#endif

#ifndef CORE_API
#define CORE_API
#endif

#include "Windows/WindowsCompiler.h"

#define DLLEXPORT					  __declspec(dllexport)
#define DLLIMPORT                     __declspec(dllimport)
#define FORCEINLINE					  __forceinline
#define FORCENOINLINE				  __declspec(noinline)
#define FORCEALIGNMENT(AlignPacking)  __declspec(align(AlignPacking))
#define DEPRECATED(Version, Message)  __declspec(deprecated("Deprecated: " Message))

#define KILOBYTE(Value)  1024LL * (Value)
#define MEGABYTE(Value)  1024LL * KILOBYTE((Value))
#define GIGABYTE(Value)  1024LL * MEGABYTE((Value))
#define TERABYTE(Value)  1024LL * GIGABYTE((Value))

#define STRUCT_OFFSET(Struct, Member) offsetof(Struct, Member)

#define Assert(Condition) if (!(Condition)) *(int *)0 = 0;
#define ArrayCount(Array) sizeof((Array)) / sizeof((Array)[0])

#define LogError(Message) Console::Print(Message); Assert(0);

#endif