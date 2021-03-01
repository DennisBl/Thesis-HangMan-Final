/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef MEMORY_ARCHIVE_H
#define MEMORY_ARCHIVE_H

#include "Archive.h"

class CORE_API FMemoryArchive : public FArchive
{
public:
    virtual FString GetArchiveName() const override 
    { 
        return FString("FMemoryArchive"); 
    }

protected:
    FORCEINLINE FMemoryArchive()
        : Offset(0)
    { }

    uint64 Offset;
};

#endif