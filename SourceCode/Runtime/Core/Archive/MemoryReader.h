/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef MEMORY_READER_H
#define MEMORY_READER_H

#include "MemoryArchive.h"

class CORE_API FMemoryReader : public FMemoryArchive
{
public:
    FMemoryReader(const TArray<uint8> &InByteCache, bool bIsPersistent = false);

    virtual bool IsLoading() const override
    {
        return true;
    }

    virtual void Serialize(void *Data, uint64 Size) override;
    virtual FString GetArchiveName() const override
    {
        return TEXT("FMemoryReader");
    }

protected:
    const TArray<uint8> &ByteCache;
};

#endif