#include "WindowsPlatformFileIni.h"

FPlatformFileIni::FPlatformFileIni(const FString &Filename)
	: Filename(Filename)
{ }

bool
FPlatformFileIni::Exists(const FString &InField) const
{
	const TCHAR *FilenameData = Filename.GetData();
	
	TCHAR SectionNames[1024];
	::GetPrivateProfileSectionNames(SectionNames, 1024, FilenameData);

	TArray<FString> FieldNames;
	FString CurrentName;

	uint32 CurrentIndex = 0;
	bool bEndReached = false;
	while (!bEndReached)
	{
		if (SectionNames[CurrentIndex] != '\0')
		{
			CurrentName.Append(SectionNames[CurrentIndex]);
		}
		else
		{
			if (!CurrentName.IsEmpty())
			{
				FieldNames.Add(CurrentName);
				CurrentName.Empty();
			}
			else
			{
				bEndReached = true;
			}
		}

		++CurrentIndex;
	}

	for (const FString &FieldName : FieldNames)
	{
		if (FieldName == InField)
		{
			return true;
		}
	}

	return false;
}

void 
FPlatformFileIni::BeginReadback(const FString &InField)
{
	ReadField = InField;
}

int32 
FPlatformFileIni::ReadInteger(const FString &InKey)
{
	const TCHAR *FilenameData = Filename.GetData();
	const TCHAR *FieldData    = ReadField.GetData();
	const TCHAR *KeyData      = InKey.GetData();

	return ::GetPrivateProfileInt(FieldData, KeyData, -1, FilenameData);
}

void 
FPlatformFileIni::EndReadback()
{
	ReadField.Empty();
}

void 
FPlatformFileIni::BeginWriteStream(const FString &InField)
{
	WriteField = InField;
}

void 
FPlatformFileIni::WriteInteger(const FString &InKey, int32 Integer)
{
	const TCHAR *FilenameData = Filename.GetData();
	const TCHAR *FieldData    = WriteField.GetData();
	const TCHAR *KeyData      = InKey.GetData();

	FString IntegerString(Integer);
	const TCHAR *IntegerStringData = IntegerString.GetData();

	::WritePrivateProfileString(FieldData, KeyData, IntegerStringData, FilenameData);
}

void 
FPlatformFileIni::EndWriteStream()
{
	WriteField.Empty();
}