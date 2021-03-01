#ifndef CSTRING_H
#define CSTRING_H

#include <CommonTypes.h>
#include <Definitions.h>
#include <string>
#include <Memory/Memory.h>

namespace CString
{
	FORCEINLINE int32 Atoi(const TCHAR *InString);
	FORCEINLINE float Atof(const TCHAR *InString);	

	FORCEINLINE TCHAR *Copy(TCHAR *OutDestination, const TCHAR *InSource);
	FORCEINLINE TCHAR *Concat(TCHAR *OutDestination, const TCHAR *InSource);
	FORCEINLINE TCHAR *SubString(const TCHAR *InString, const TCHAR *InSubString);
	FORCEINLINE int32 Compare(const TCHAR *InFirstString, const TCHAR *InSecondString);
	FORCEINLINE int32 GetLength(const TCHAR *InString);

	FORCEINLINE bool IsNumeric(const TCHAR *InString);
};

#include "CString.inl"

#endif 