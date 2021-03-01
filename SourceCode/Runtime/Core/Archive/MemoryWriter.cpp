/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#include "MemoryWriter.h"

FMemoryWriter::FMemoryWriter(TArray<uint8> &InByteCache, bool bIsPersistent)
    : ByteCache(InByteCache)
{
    Offset = ByteCache.GetCapacity();
}

void 
FMemoryWriter::Serialize(void *Data, uint64 Size)
{
    ByteCache.Resize(Offset + Size);
    FMemory::Copy(&ByteCache[Offset], Data, Size);
    Offset += Size;
}