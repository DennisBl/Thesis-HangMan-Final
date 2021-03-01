/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <Container/Array.h>
#include <Container/String.h>
#include <Memory/Memory.h>

struct FArchiveHeader
{
	TCHAR Name[4];
	uint16 MajorVersion;
	uint16 MinorVersion;
	uint64 Capacity;
};

class CORE_API FArchive
{
public:
	virtual ~FArchive()
	{

	}

	virtual void Serialize(void *Data, uint64 Size)
	{
		
	}

	virtual void SerializeBits(void *Data, uint64 BitSize)
	{
		Serialize(Data, (BitSize + 7) / 8);

		if (BitSize % 8)
		{
			((uint8 *)Data)[BitSize / 8] &= ((1 << (BitSize & 7)) - 1);
		}
	}

	virtual bool IsLoading() const
	{
		return false;
	}

	virtual bool IsSaving() const
	{
		return false;
	}

	FArchive &operator<<(uint8 &Value)
	{
		Serialize(&Value, sizeof(uint8));
		return *this;
	}

	FArchive &operator<<(int8 &Value)
	{
		Serialize(&Value, sizeof(int8));
		return *this;
	}

	FArchive &operator<<(uint16 &Value)
	{
		Serialize(&Value, sizeof(uint16));
		return *this;
	}

	FArchive &operator<<(int16 &Value)
	{
		Serialize(&Value, sizeof(int16));
		return *this;
	}

	FArchive &operator<<(uint32 &Value)
	{
		Serialize(&Value, sizeof(uint32));
		return *this;
	}

	FArchive &operator<<(int32 &Value)
	{
		Serialize(&Value, sizeof(int32));
		return *this;
	}

	FArchive &operator<<(uint64 &Value)
	{
		Serialize(&Value, sizeof(uint64));
		return *this;
	}

	FArchive &operator<<(int64 &Value)
	{
		Serialize(&Value, sizeof(int64));
		return *this;
	}

	FArchive &operator<<(float &Value)
	{
		Serialize(&Value, sizeof(float));
		return *this;
	}

	FArchive &operator<<(double &Value)
	{
		Serialize(&Value, sizeof(double));
		return *this;
	}

	virtual FString GetArchiveName() const = 0;
};

#endif