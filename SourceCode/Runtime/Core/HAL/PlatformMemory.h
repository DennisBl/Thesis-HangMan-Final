#ifndef HAL_PLATFORM_MEMORY_H
#define HAL_PLATFORM_MEMORY_H

#include <Definitions.h>

#if PLATFORM_WINDOWS
#include "../Windows/WindowsMemory.h"
#elif PLATFORM_LINUX
#include "../Linux/LinuxMemory.h"
#elif PLATFORM_ANDROID
#include "../Android/AndroidMemory.h"
#elif PLATFORM_IOS
#include "../Apple/AppleMemory.h"
#endif

#endif