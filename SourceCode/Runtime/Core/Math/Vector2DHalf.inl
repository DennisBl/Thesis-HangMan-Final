/* =====================================================================
   Creator: Calestian
   Project: Game Core
   Date: N/A
   Revision: N/A
   Copyright: (C) Copyright 2015 by Calestian, Inc. All Rights Reserved.
   ===================================================================== */

FORCEINLINE
FVector2DHalf::FVector2DHalf()
	: X(0)
	, Y(0)
{ }

FORCEINLINE 
FVector2DHalf::FVector2DHalf(float InX, float InY)
	: X(InX)
	, Y(InY)
{ }

FORCEINLINE 
FVector2DHalf::FVector2DHalf(const Float16 &InX, const Float16 &InY)
	: X(InX)
	, Y(InY)
{ }

FORCEINLINE
FVector2DHalf::FVector2DHalf(const FVector2D &InVector)
	: X(InVector.X)
	, Y(InVector.Y)
{ }

FORCEINLINE 
FVector2DHalf::FVector2DHalf(const FVector2DHalf &Copy)
	: X(Copy.X)
	, Y(Copy.Y)
{ }