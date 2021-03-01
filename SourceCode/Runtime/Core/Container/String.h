#ifndef STRING_H
#define STRING_H

#include "CString.h"

class FString
{
public:
	FORCEINLINE FString();
	FORCEINLINE FString(const FString &InString);
	FORCEINLINE FString(const TCHAR *InString);
	FORCEINLINE FString(const char &InChar);

	FORCEINLINE explicit FString(int32 Int);
	FORCEINLINE explicit FString(uint32 UInt);
	FORCEINLINE explicit FString(float Float);

	FORCEINLINE ~FString();

	FORCEINLINE FString &Resize(uint32 InLength);
	FORCEINLINE FString &SubString(uint32 Start, uint32 End);
	FORCEINLINE FString &Copy(const FString &InString);
	FORCEINLINE FString &Append(const FString &InString);
	FORCEINLINE FString &Insert(const FString &InString, uint32 Index);
	FORCEINLINE FString &Remove(uint32 Index, uint32 Count = 1);
	FORCEINLINE FString &Replace(const FString &InDestination, const FString &InSource);

	FORCEINLINE bool Compare(const FString &InString) const;
	FORCEINLINE bool Contains(const FString &InString) const;
	FORCEINLINE void Empty();

	FORCEINLINE int32 SearchLast(const FString &InString) const;
	FORCEINLINE int32 Search(const FString &InString, uint32 Offset = 0) const;
	FORCEINLINE uint32 GetLength() const;

	FORCEINLINE bool IsEmpty() const;
	FORCEINLINE bool IsNumeric() const;

	FORCEINLINE TCHAR *GetData();
	FORCEINLINE const TCHAR *GetData() const;

	FORCEINLINE char &operator[](int32 Index) const;

	FORCEINLINE FString operator+(const FString &InString) const;

	FORCEINLINE FString &operator =(const FString &InString);
	FORCEINLINE FString &operator+=(const FString &InString);

	FORCEINLINE bool operator==(const FString &InString) const;
	FORCEINLINE bool operator!=(const FString &InString) const;

private:
	FORCEINLINE friend       TCHAR *begin(FString &InString)       { return InString.GetData(); }
	FORCEINLINE friend const TCHAR *begin(const FString &InString) { return InString.GetData(); }
	FORCEINLINE friend       TCHAR *end(FString &InString)         { return InString.GetData() + InString.GetLength(); }
	FORCEINLINE friend const TCHAR *end(const FString &InString)   { return InString.GetData() + InString.GetLength(); }

private:
	void ResizeInternal(uint32 InLength)
	{
		Length = InLength;
		CharData = (TCHAR *)FMemory::Realloc(CharData, Length + 1);
		CharData[Length] = 0;
	}

	void CopyInternal(const TCHAR *InSource, uint32 InLength)
	{
		Length = InLength;
		CharData = (TCHAR *)FMemory::Realloc(CharData, Length + 1);
		CString::Copy(CharData, InSource);
	}

	void AppendInternal(const TCHAR *InSource, uint32 InLength)
	{
		Length += InLength;
		CharData = (TCHAR *)FMemory::Realloc(CharData, Length + 1);
		CString::Concat(CharData, InSource);
	}

	void CopyToEmpty(const TCHAR *InSource, uint32 InLength)
	{
		Length = InLength;
		CharData = (TCHAR *)FMemory::Malloc(Length + 1);
		CString::Copy(CharData, InSource);
	}

private:
	TCHAR *CharData;
	uint32 Length;
};

FORCEINLINE FString operator+(const TCHAR *InStringA, const FString &InStringB);

#include "String.inl"

#endif