/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef MEMORY_WRITER_H
#define MEMORY_WRITER_H

#include "MemoryArchive.h"

class CORE_API FMemoryWriter : public FMemoryArchive
{
public:
    FMemoryWriter(TArray<uint8> &InByteCache, bool bIsPersistent = false);

    virtual bool IsSaving() const override
    {
        return true;
    }

    virtual void Serialize(void *Data, uint64 Size) override;
    virtual FString GetArchiveName() const override 
    { 
        return TEXT("FMemoryWriter"); 
    }

protected:
    TArray<uint8> &ByteCache;
};

#endif