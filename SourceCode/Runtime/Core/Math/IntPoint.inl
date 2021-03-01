FORCEINLINE 
FIntPoint::FIntPoint()
	: X(0)
	, Y(0)
{ }

FORCEINLINE 
FIntPoint::FIntPoint(int32 X, int32 Y)
	: X(X)
	, Y(Y)
{ }

FORCEINLINE 
FIntPoint::FIntPoint(const FIntPoint &Other)
	: X(Other.X)
	, Y(Other.Y)
{ }

FORCEINLINE 
FIntPoint::FIntPoint(const FVector2D &Other)
	: X(Other.X)
	, Y(Other.Y)
{ }

FORCEINLINE 
FIntPoint::FIntPoint(int32 Value)
	: X(Value)
	, Y(Value)
{ }

FORCEINLINE FIntPoint &
FIntPoint::Clamp(const FIntPoint &InPoint)
{
	X = FMath::Clamp(X, InPoint.X, InPoint.Y);
	Y = FMath::Clamp(Y, InPoint.X, InPoint.Y);
	return *this;
}

FORCEINLINE bool 
FIntPoint::InsideRect(const FIntRect &InRect) const
{
	return X > InRect.Min.X && X < InRect.Min.X + InRect.Max.X && Y > InRect.Min.Y && Y < InRect.Min.Y + InRect.Max.Y;
}

FORCEINLINE FVector2D 
FIntPoint::ToVector2D() const
{
	return FVector2D(X, Y);
}

FORCEINLINE FIntPoint
FIntPoint::operator+(float Value) const
{
	return FIntPoint(X + Value, Y + Value);
}

FORCEINLINE FIntPoint
FIntPoint::operator+(const FIntPoint &Other) const
{
	return FIntPoint(X + Other.X, Y + Other.Y);
}

FORCEINLINE FIntPoint
FIntPoint::operator+(const FVector2D &Other) const
{
	return FIntPoint(X + Other.X, Y + Other.Y);
}

FORCEINLINE FIntPoint
FIntPoint::operator-(float Value) const
{
	return FIntPoint(X - Value, Y - Value);
}

FORCEINLINE FIntPoint 
FIntPoint::operator-(const FIntPoint &Other) const
{
	return FIntPoint(X - Other.X, Y - Other.Y);
}

FORCEINLINE FIntPoint 
FIntPoint::operator-(const FVector2D &Other) const
{
	return FIntPoint(X - Other.X, Y - Other.Y);
}

FORCEINLINE FIntPoint 
FIntPoint::operator*(float Value) const
{
	return FIntPoint(X * Value, Y * Value);
}

FORCEINLINE FIntPoint 
FIntPoint::operator*(const FIntPoint &Other) const
{
	return FIntPoint(X * Other.X, Y * Other.Y);
}

FORCEINLINE FIntPoint
FIntPoint::operator*(const FVector2D &Other) const
{
	return FIntPoint(X * Other.X, Y * Other.Y);
}

FORCEINLINE FIntPoint
FIntPoint::operator/(float Value) const
{
	return FIntPoint(X / Value, Y / Value);
}

FORCEINLINE FIntPoint
FIntPoint::operator/(const FIntPoint &Other) const
{
	return FIntPoint(X / Other.X, Y / Other.Y);
}

FORCEINLINE FIntPoint 
FIntPoint::operator/(const FVector2D &Other) const
{
	return FIntPoint(X / Other.X, Y / Other.Y);
}

FORCEINLINE FIntPoint &
FIntPoint::operator =(const FIntPoint &Other)
{
	X = Other.X;
	Y = Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator+=(float Value)
{
	X += Value;
	Y += Value;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator+=(const FIntPoint &Other)
{
	X += Other.X;
	Y += Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator+=(const FVector2D &Other)
{
	X += Other.X;
	Y += Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator-=(float Value)
{
	X += Value;
	Y += Value;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator-=(const FIntPoint &Other)
{
	X -= Other.X;
	Y -= Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator-=(const FVector2D &Other)
{
	X -= Other.X;
	Y -= Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator*=(float Value)
{
	X += Value;
	Y += Value;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator*=(const FIntPoint &Other)
{
	X *= Other.X;
	Y *= Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator*=(const FVector2D &Other)
{
	X *= Other.X;
	Y *= Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator/=(float Value)
{
	X += Value;
	Y += Value;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator/=(const FIntPoint &Other)
{
	X /= Other.X;
	Y /= Other.Y;
	return *this;
}

FORCEINLINE FIntPoint &
FIntPoint::operator/=(const FVector2D &Other)
{
	X /= Other.X;
	Y /= Other.Y;
	return *this;
}

FORCEINLINE bool 
FIntPoint::operator==(const FIntPoint &Other) const
{
	return X == Other.X && Y == Other.Y;
}

FORCEINLINE bool 
FIntPoint::operator!=(const FIntPoint &Other) const
{
	return !(*this == Other);
}