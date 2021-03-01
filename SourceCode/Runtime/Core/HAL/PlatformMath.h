#ifndef HAL_PLATFORM_MATH_H
#define HAL_PLATFORM_MATH_H

#include <Definitions.h>

#if PLATFORM_WINDOWS
#include "../Windows/WindowsMath.h"
#elif PLATFORM_LINUX
#include "../Linux/LinuxMath.h"
#elif PLATFORM_ANDROID
#include "../Android/AndroidMath.h"
#elif PLATFORM_IOS
#include "../Apple/AppleMath.h"
#endif

#endif