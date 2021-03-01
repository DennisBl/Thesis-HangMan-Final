#ifndef PLATFORM_H
#define PLATFORM_H

#include <CoreMinimal.h>

#if PLATFORM_WINDOWS
#include "Windows/WindowsWindow.h"
#include "Windows/WindowsApplication.h"
#include "Windows/WindowsPlatformFileIni.h"
#elif PLATFORM_LINUX
#elif PLATFORM_IOS
#elif PLATFORM_ANDROID
#endif

#endif