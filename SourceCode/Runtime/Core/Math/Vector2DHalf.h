/* =====================================================================
   Creator: Calestian
   Project: Game Core
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

#ifndef VECTOR_2D_HALF_H
#define VECTOR_2D_HALF_H

#include "Float16.h"
#include "Vector2D.h"

class FVector2DHalf
{
public:
	Float16 X;
	Float16 Y;

public:
	FORCEINLINE FVector2DHalf();
	FORCEINLINE FVector2DHalf(float InX, float InY);
	FORCEINLINE FVector2DHalf(const Float16 &InX, const Float16 &InY);
	FORCEINLINE FVector2DHalf(const FVector2D &InVector);
	FORCEINLINE FVector2DHalf(const FVector2DHalf &Copy);
};

#include "Vector2DHalf.inl"

#endif