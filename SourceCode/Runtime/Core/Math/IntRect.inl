FORCEINLINE 
FIntRect::FIntRect()
{ }

FORCEINLINE 
FIntRect::FIntRect(int32 MinX, int32 MinY, int32 MaxX, int32 MaxY)
	: Min(FIntPoint(MinX, MinY))
	, Max(FIntPoint(MaxX, MaxY))
{ }

FORCEINLINE 
FIntRect::FIntRect(const FIntRect &Other)
	: Min(Other.Min)
	, Max(Other.Max)
{ }

FORCEINLINE 
FIntRect::FIntRect(const FVector4D &Other)
	: Min(FIntPoint(Other.X, Other.Y))
	, Max(FIntPoint(Other.Z, Other.W))
{ }

FORCEINLINE 
FIntRect::FIntRect(float Value)
	: Min(Value)
	, Max(Value)
{ }

FORCEINLINE 
FIntRect::FIntRect(const FVector2D &Min, const FVector2D &Max)
	: Min(FIntPoint(Min.X, Min.Y))
	, Max(FIntPoint(Max.X, Max.Y))
{ }

FORCEINLINE
FIntRect::FIntRect(const FIntPoint &Min, const FIntPoint &Max)
	: Min(FIntPoint(Min.X, Min.Y))
	, Max(FIntPoint(Max.X, Max.Y))
{ }

FORCEINLINE FIntRect &
FIntRect::Clamp(const FIntPoint &InMin, const FIntPoint &InMax)
{
	Min.Clamp(InMin);
	Max.Clamp(InMax);
	return *this;
}

FORCEINLINE bool
FIntRect::InsideRect(const FIntRect &InRect) const
{
	return Min.InsideRect(InRect) && Max.InsideRect(InRect);
}

FORCEINLINE FVector4D
FIntRect::ToVector4D() const
{
	return FVector4D(Min.X, Min.Y, Max.X, Max.Y);
}

FORCEINLINE int32 
FIntRect::GetOriginX() const
{
	return Min.X;
}

FORCEINLINE int32 
FIntRect::GetOriginY() const
{
	return Min.Y;
}

FORCEINLINE FIntPoint 
FIntRect::GetOrigin() const
{
	FIntPoint Origin;
	Origin.X = GetOriginX();
	Origin.Y = GetOriginY();
	return Origin;
}

FORCEINLINE int32 
FIntRect::GetSizeX() const
{
	return Max.X - Min.X;
}

FORCEINLINE int32 
FIntRect::GetSizeY() const
{
	return Max.Y - Min.Y;
}

FORCEINLINE FIntPoint 
FIntRect::GetSize() const
{
	FIntPoint Size;
	Size.X = GetSizeX();
	Size.Y = GetSizeY();
	return Size;
}

FORCEINLINE FIntRect
FIntRect::operator+(float Value) const
{
	return FIntRect(Min + Value, Max + Value);
}

FORCEINLINE FIntRect
FIntRect::operator+(const FIntRect &Other) const
{
	return FIntRect(Min + Other.Min, Max + Other.Max);
}

FORCEINLINE FIntRect
FIntRect::operator+(const FVector4D &Other) const
{
	return FIntRect(Min.X + Other.X, Min.Y + Other.Y, Max.X + Other.Z, Max.Y + Other.W);
}

FORCEINLINE FIntRect
FIntRect::operator-(float Value) const
{
	return FIntRect(Min - Value, Max - Value);
}

FORCEINLINE FIntRect
FIntRect::operator-(const FIntRect &Other) const
{
	return FIntRect(Min - Other.Min, Max - Other.Max);
}

FORCEINLINE FIntRect
FIntRect::operator-(const FVector4D &Other) const
{
	return FIntRect(Min.X - Other.X, Min.Y - Other.Y, Max.X - Other.Z, Max.Y - Other.W);
}

FORCEINLINE FIntRect
FIntRect::operator*(float Value) const
{
	return FIntRect(Min * Value, Max * Value);
}

FORCEINLINE FIntRect
FIntRect::operator*(const FIntRect &Other) const
{
	return FIntRect(Min * Other.Min, Max * Other.Max);
}

FORCEINLINE FIntRect
FIntRect::operator*(const FVector4D &Other) const
{
	return FIntRect(Min.X * Other.X, Min.Y * Other.Y, Max.X * Other.Z, Max.Y * Other.W);
}

FORCEINLINE FIntRect
FIntRect::operator/(float Value) const
{
	return FIntRect(Min / Value, Max / Value);
}

FORCEINLINE FIntRect
FIntRect::operator/(const FIntRect &Other) const
{
	return FIntRect(Min / Other.Min, Max / Other.Max);
}

FORCEINLINE FIntRect
FIntRect::operator/(const FVector4D &Other) const
{
	return FIntRect(Min.X / Other.X, Min.Y / Other.Y, Max.X / Other.Z, Max.Y / Other.W);
}

FORCEINLINE FIntRect &
FIntRect::operator=(const FIntRect &Other)
{
	Min = Other.Min;
	Max = Other.Max;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator+=(float Value)
{
	Min += Value;
	Max += Value;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator+=(const FIntRect &Other)
{
	Min += Other.Min;
	Max += Other.Max;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator+=(const FVector4D &Other)
{
	Min += FVector2D(Other.X, Other.Y);
	Max += FVector2D(Other.Z, Other.W);
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator-=(float Value)
{
	Min -= Value;
	Max -= Value;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator-=(const FIntRect &Other)
{
	Min -= Other.Min;
	Max -= Other.Max;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator-=(const FVector4D &Other)
{
	Min -= FVector2D(Other.X, Other.Y);
	Max -= FVector2D(Other.Z, Other.W);
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator*=(float Value)
{
	Min *= Value;
	Max *= Value;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator*=(const FIntRect &Other)
{
	Min *= Other.Min;
	Max *= Other.Max;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator*=(const FVector4D &Other)
{
	Min *= FVector2D(Other.X, Other.Y);
	Max *= FVector2D(Other.Z, Other.W);
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator/=(float Value)
{
	Min /= Value;
	Max /= Value;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator/=(const FIntRect &Other)
{
	Min /= Other.Min;
	Max /= Other.Max;
	return *this;
}

FORCEINLINE FIntRect &
FIntRect::operator/=(const FVector4D &Other)
{
	Min /= FVector2D(Other.X, Other.Y);
	Max /= FVector2D(Other.Z, Other.W);
	return *this;
}

FORCEINLINE bool
FIntRect::operator==(const FIntRect &Other) const
{
	return Min == Other.Min && Max == Other.Max;
}

FORCEINLINE bool
FIntRect::operator!=(const FIntRect &Other) const
{
	return !(*this == Other);
}