#include <stdlib.h>
#include <Memory/Memory.h>

FORCEINLINE int32 
CString::Atoi(const TCHAR *InString)
{
	return atoi(InString);
}

FORCEINLINE float
CString::Atof(const TCHAR *InString)
{
	return atof(InString);
}

FORCEINLINE TCHAR *
CString::Copy(TCHAR *OutDestination, const TCHAR *InSource)
{
	return strcpy(OutDestination, InSource);
}

FORCEINLINE TCHAR *
CString::Concat(TCHAR *OutDestination, const TCHAR *InSource)
{
	return strcat(OutDestination, InSource);
}

FORCEINLINE TCHAR *
CString::SubString(const TCHAR *InString, const TCHAR *InSubString)
{
	return (TCHAR *)strstr(InString, InSubString);
}

FORCEINLINE int32
CString::Compare(const TCHAR *InFirstString, const TCHAR *InSecondString)
{
	return !strcmp(InFirstString, InSecondString);
}

FORCEINLINE int32 
CString::GetLength(const TCHAR *InString)
{
	return strlen(InString);
}

FORCEINLINE bool
CString::IsNumeric(const TCHAR *InString)
{
	if (*InString == '-' || *InString == '+')
	{
		InString++;
	}

	bool bContainsDot = false;
	while (*InString != '\0')
	{
		if (*InString == '.')
		{
			if (bContainsDot)
			{
				return false;
			}

			bContainsDot = true;
		}
		else if (!::isdigit(*InString))
		{
			return false;
		}

		++InString;
	}

	return true;
}