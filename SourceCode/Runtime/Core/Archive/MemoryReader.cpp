/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#include "MemoryReader.h"

FMemoryReader::FMemoryReader(const TArray<uint8> &InByteCache, bool bIsPersistent)
    : ByteCache(InByteCache)
{ 
    Offset = 0;
}

void 
FMemoryReader::Serialize(void *Data, uint64 Size)
{
    uint64 TotalSize = ByteCache.GetCapacity();
    if (Offset + Size <= TotalSize)
    {
        FMemory::Copy(Data, &ByteCache[Offset], Size);
        Offset += Size;
    }
}