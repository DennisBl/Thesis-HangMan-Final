FORCEINLINE 
FVector2D::FVector2D()
	: X(0)
	, Y(0)
{ }

FORCEINLINE
FVector2D::FVector2D(float Value)
	: X(Value)
	, Y(Value)
{ }

FORCEINLINE
FVector2D::FVector2D(const FVector3D &Other)
	: X(Other.X)
	, Y(Other.Y)
{ }

FORCEINLINE
FVector2D::FVector2D(const FVector4D &Other)
	: X(Other.X)
	, Y(Other.Y)
{ }

FORCEINLINE
FVector2D::FVector2D(float X, float Y)
	: X(X)
	, Y(Y)
{ }

FORCEINLINE
FVector2D::FVector2D(const FVector2D &Other)
	: X(Other.X)
	, Y(Other.Y)
{ }

FORCEINLINE float &
FVector2D::operator[](uint32 Index)
{
	Assert(Index < 2);
	return (&X)[Index];
}

FORCEINLINE float 
FVector2D::operator[](uint32 Index) const
{
	Assert(Index < 2);
	return (&X)[Index];
}

FORCEINLINE FVector2D 
FVector2D::operator-() const
{
	return FVector2D(-X, -Y);
}

FORCEINLINE FVector2D 
FVector2D::operator+(float Value) const
{
	return FVector2D(X + Value, Y + Value);
}

FORCEINLINE FVector2D
FVector2D::operator+(const FVector2D &Other) const
{
	return FVector2D(X + Other.X, Y + Other.Y);
}

FORCEINLINE FVector2D 
FVector2D::operator-(float Value) const
{
	return FVector2D(X - Value, Y - Value);
}

FORCEINLINE FVector2D 
FVector2D::operator-(const FVector2D &Other) const
{
	return FVector2D(X - Other.X, Y - Other.Y);
}

FORCEINLINE FVector2D 
FVector2D::operator*(float Value) const
{
	return FVector2D(X * Value, Y * Value);
}

FORCEINLINE FVector2D 
FVector2D::operator*(const FVector2D &Other) const
{
	return FVector2D(X * Other.X, Y * Other.Y);
}

FORCEINLINE FVector2D 
FVector2D::operator/(float Value) const
{
	return FVector2D(X / Value, Y / Value);
}

FORCEINLINE FVector2D 
FVector2D::operator/(const FVector2D &Other) const
{
	return FVector2D(X / Other.X, Y / Other.Y);
}

FORCEINLINE FVector2D &
FVector2D::operator=(float Value)
{
	X = Value;
	Y = Value;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator=(const FVector2D &Other)
{
	X = Other.X;
	Y = Other.Y;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator+=(float Value)
{
	X += Value;
	Y += Value;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator+=(const FVector2D &Other)
{
	X += Other.X;
	Y += Other.Y;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator-=(float Value)
{
	X -= Value;
	Y -= Value;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator-=(const FVector2D &Other)
{
	X -= Other.X;
	Y -= Other.Y;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator*=(float Value)
{
	X *= Value;
	Y *= Value;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator*=(const FVector2D &Other)
{
	X *= Other.X;
	Y *= Other.Y;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator/=(float Value)
{
	X /= Value;
	Y /= Value;
	return *this;
}

FORCEINLINE FVector2D &
FVector2D::operator/=(const FVector2D &Other)
{
	X /= Other.X;
	Y /= Other.Y;
	return *this;
}

FORCEINLINE bool 
FVector2D::operator==(const FVector2D &Other) const
{
	return X == Other.X && Y == Other.Y;
}

FORCEINLINE bool 
FVector2D::operator!=(const FVector2D &Other) const
{
	return !(*this == Other);
}