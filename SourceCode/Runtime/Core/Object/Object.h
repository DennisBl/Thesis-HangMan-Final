/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef OBJECT_H
#define OBJECT_H

#include <Archive/Archive.h>
#include <Memory/RefCountedObject.h>

class CORE_API FObject : public FRefCountedObject
{
public:
    virtual void OnPreLoad();
    virtual void OnPostLoad();
    virtual void OnPreSave();
    virtual void OnPostSave();
    virtual void Serialize(FArchive &Archive);

    template <class TCompareType>
    FORCEINLINE bool Is()
    {
        return dynamic_cast<TCompareType *>(this) != 0;
    }
};

#endif