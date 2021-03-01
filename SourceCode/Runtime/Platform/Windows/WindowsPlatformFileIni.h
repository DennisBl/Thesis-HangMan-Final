#ifndef WINDOWS_PLATFORM_FILE_INI
#define WINDOWS_PLATFORM_FILE_INI

#include <CoreMinimal.h>

class FPlatformFileIni
{
public:
	FString Filename;
	FString ReadField;
	FString WriteField;

public:
	FPlatformFileIni(const FString &Filename);

	bool Exists(const FString &InField) const;

	void BeginReadback(const FString &InField);
	int32 ReadInteger(const FString &InKey);
	void EndReadback();

	void BeginWriteStream(const FString &InField);
	void WriteInteger(const FString &InKey, int32 Integer);
	void EndWriteStream();
};

#endif