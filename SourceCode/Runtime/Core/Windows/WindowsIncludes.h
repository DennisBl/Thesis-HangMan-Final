#ifndef WINDOWS_PLATFORM_INCLUDES_H
#define WINDOWS_PLATFORM_INCLUDES_H

#define VC_EXTRALEAN 
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>

#ifdef SetWindowText
#undef SetWindowText
#endif


#ifdef CreateWindow
#undef CreateWindow
#endif

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#endif