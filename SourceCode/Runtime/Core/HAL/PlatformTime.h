#ifndef HAL_PLATFORM_TIME_H
#define HAL_PLATFORM_TIME_H

#include <Definitions.h>

#if PLATFORM_WINDOWS
#include "../Windows/WindowsTime.h"
#elif PLATFORM_LINUX
#include "../Linux/LinuxTime.h"
#elif PLATFORM_ANDROID
#include "../Android/AndroidTime.h"
#elif PLATFORM_IOS
#include "../Apple/AppleTime.h"
#endif

#endif