/* =====================================================================
   Creator: Calestian
   Project: Game Engine
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef CLASS_H
#define CLASS_H

#include "Object.h"

class FClassProperty
{
public:
    void *Data;
    int32 Capacity;
};

class FClassFunction
{
public:
    bool bIsVirtual;
};

class CORE_API FClass : public FObject
{
protected:
	enum EClassPropertyType
	{
		Transient,
		Persistent,
		ReadOnly,
		ReadWrite,
	};

public:
    TArray<FClassProperty> Properties;
    TArray<FClassFunction> Functions;

	uint16 BaseClassId;
	uint16 DerivedClassId;

public:
    void RegisterProperty(const FClassProperty &Property) { }
    void UnregisterProperty(const FClassProperty &Property) { }
    void UpdateProperty(const FClassProperty &Property) { }
    void RegisterFunction(const FClassFunction &Function) { }
    void UnregisterFunction(const FClassFunction &Function) { }
    void UpdateFuction(const FClassFunction &Function) { }
	void ExecuteFunction(const FClassFunction &Function) { }
};

#define GET_CLASS_HASH_INDEX(ClassName) typeid(ClassName).hash_code()
#define REGISTER_CLASS(ClassName) \
		class FClassMapItem_##ClassName : public FClassMapItem \
		{ \
		public: \
			FORCEINLINE FClassMapItem_##ClassName() \
			{ \
				GlobalObjects.Add(GetHashId(), this); \
			} \
			virtual FClass *CreateStatic() override \
			{ \
				return new ClassName(); \
			} \
			virtual uint32 GetHashId() override \
			{ \
				return GET_CLASS_HASH_INDEX(ClassName); \
			} \
		}; \
		static FClassMapItem_##ClassName _##ClassName;
#define REGISTER_CLASS_INITIALIZER(BaseClassName, DerivedClassName) \
		typedef DerivedClassName Super; \
		class FClass_##BaseClassName_Initializer \
		{ \
		public: \
			FORCEINLINE FClass_##BaseClassName_Initializer(FClass *Class) \
			{ \
				Class->BaseClassId = GET_CLASS_HASH_INDEX(BaseClassName); \
				Class->DerivedClassId = GET_CLASS_HASH_INDEX(DerivedClassName); \
			} \
		}; \
		FClass_##BaseClassName_Initializer _##BaseClassName_Initializer = FClass_##BaseClassName_Initializer(this);
#define REGISTER_CLASS_PROPERTY(PropertyName, ProperyAccess) \
		class FClassProperty_##PropertyName \
		{ \
		public: \
			FORCEINLINE FClassProperty_##PropertyName(FClass *Class) \
			{ \
				FClassProperty _Property; \
				Class->Properties.Add(_Property); \
			} \
		}; \
		FClassProperty_##PropertyName _##PropertyName = FClassProperty_##PropertyName(this);
#define CREATE_STATIC_CLASS(ClassName) GlobalObjects[GET_CLASS_HASH_INDEX(ClassName)]->CreateStatic()

class FClassMapItem
{
public:
	virtual FClass *CreateStatic() = 0;
	virtual uint32 GetHashId() = 0;
};

extern TMap<uint16, FClassMapItem *> GlobalObjects;

#endif