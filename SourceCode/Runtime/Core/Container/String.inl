FORCEINLINE
FString::FString()
	: CharData(0)
	, Length(0)
{
	CharData = (TCHAR *)FMemory::Malloc(1);
	CharData[0] = 0;
}

FORCEINLINE
FString::FString(const FString &InString)
	: CharData(0)
	, Length(0)
{
	CopyToEmpty(InString.CharData, InString.Length);
}

FORCEINLINE
FString::FString(const TCHAR *InString)
	: CharData(0)
	, Length(0)
{
	CopyToEmpty(InString, CString::GetLength(InString));
}

FORCEINLINE 
FString::FString(const char &InChar)
	: CharData(0)
	, Length(1)
{
	ResizeInternal(1);
	CharData[0] = InChar;
}

FORCEINLINE
FString::FString(int32 Int)
	: CharData(0)
	, Length(0)
{
	char Buffer[128];
	sprintf_s(Buffer, "%d", Int);

	CopyToEmpty(Buffer, CString::GetLength(Buffer));
}

FORCEINLINE
FString::FString(uint32 UInt)
	: CharData(0)
	, Length(0)
{
	char Buffer[128];
	sprintf_s(Buffer, "%u", UInt);

	CopyToEmpty(Buffer, CString::GetLength(Buffer));
}

FORCEINLINE
FString::FString(float Float)
	: CharData(0)
	, Length(0)
{
	char Buffer[128];
	sprintf_s(Buffer, "%.02f", Float);

	CopyToEmpty(Buffer, CString::GetLength(Buffer));
}

FORCEINLINE
FString::~FString()
{
	FMemory::Free(CharData);
}

FORCEINLINE FString &
FString::Resize(uint32 InLength)
{
	ResizeInternal(InLength);
	return *this;
}

FORCEINLINE FString & 
FString::SubString(uint32 Start, uint32 End)
{
	void *Source = CharData + Start;
	FMemory::Move(CharData, Source, End - Start);
	ResizeInternal(End - Start);
	return *this;
}

FORCEINLINE FString &
FString::Copy(const FString &InString)
{
	CopyInternal(InString.CharData, InString.Length);
	return *this;
}

FORCEINLINE FString &
FString::Append(const FString &InString)
{
	AppendInternal(InString.CharData, InString.Length);
	return *this;
}

FORCEINLINE FString &
FString::Insert(const FString &InString, uint32 Index)
{
	uint32 OriginalLength = Length;

	ResizeInternal(Length + InString.Length);
	FMemory::Move(CharData + Index + InString.Length, CharData + Index, OriginalLength - Index);
	FMemory::Copy(CharData + Index, InString.CharData, InString.Length);
	return *this;
}

FORCEINLINE FString &
FString::Remove(uint32 Index, uint32 Count)
{
	FMemory::Copy(CharData + Index, CharData + Index + Count, Length - Index - Count);
	ResizeInternal(Length - Count);
	return *this;
}

FORCEINLINE FString &
FString::Replace(const FString &InDestination, const FString &InSource)
{
	int32 DestIndex = Search(InDestination);

	if (DestIndex != -1)
	{
		Remove(DestIndex, InDestination.Length);
		Insert(InSource, DestIndex);
	}
	return *this;
}

FORCEINLINE void
FString::Empty()
{
	Resize(0);
}

FORCEINLINE bool
FString::Compare(const FString &InString) const
{
	return CString::Compare(CharData, InString.CharData);
}

FORCEINLINE bool
FString::Contains(const FString &InString) const
{
	return CString::SubString(CharData, InString.CharData);
}

FORCEINLINE int32
FString::Search(const FString &InString, uint32 Offset) const
{
	TCHAR *Found = CString::SubString(CharData + Offset, InString.CharData);
	return Found ? Found - CharData : -1;
}

FORCEINLINE int32
FString::SearchLast(const FString &InString) const
{
	int32 Output = Search(InString);
	while (Output != -1 && Search(InString, Output + 1) != -1)
	{
		Output = Search(InString, Output + 1);
	}

	return Output;
}

FORCEINLINE uint32
FString::GetLength() const
{
	return Length;
}

FORCEINLINE bool 
FString::IsEmpty() const
{
	return Length == 0;
}

FORCEINLINE bool 
FString::IsNumeric() const
{
	if (IsEmpty())
	{
		return false;
	}

	return CString::IsNumeric(CharData);
}

FORCEINLINE TCHAR *
FString::GetData()
{
	return CharData;
}

FORCEINLINE const TCHAR *
FString::GetData() const
{
	return CharData;
}

FORCEINLINE char &
FString::operator[](int32 Index) const
{
	return CharData[Index];
}

FORCEINLINE FString 
FString::operator+(const FString &InString) const
{
	FString Result = *this;
	Result.Append(InString);
	return Result;
}

FORCEINLINE FString &
FString::operator=(const FString &InString)
{
	Copy(InString);
	return *this;
}

FORCEINLINE FString &
FString::operator+=(const FString &InString)
{
	Append(InString);
	return *this;
}

FORCEINLINE bool
FString::operator==(const FString &InString) const
{
	return CString::Compare(CharData, InString.CharData);
}

FORCEINLINE bool
FString::operator!=(const FString &InString) const
{
	return !(*this == InString);
}

FORCEINLINE FString
operator+(const TCHAR *InStringA, const FString &InStringB)
{
	return FString(InStringA) + InStringB;
}