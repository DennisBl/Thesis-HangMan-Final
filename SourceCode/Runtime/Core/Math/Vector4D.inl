FORCEINLINE 
FVector4D::FVector4D()
	: Register(_mm_setzero_ps())
{ }

FORCEINLINE
FVector4D::FVector4D(float X, float Y, float Z, float W)
	: Register(_mm_set_ps(W, Z, Y, X))
{ }

FORCEINLINE
FVector4D::FVector4D(const FVector4D &Other)
	: Register(Other.Register)
{ }

FORCEINLINE
FVector4D::FVector4D(const __m128 &InRegister)
	: Register(InRegister)
{ }

FORCEINLINE
FVector4D::FVector4D(float Value)
	: Register(_mm_set1_ps(Value))
{ }

FORCEINLINE
FVector4D::FVector4D(const FVector3D &InVectorXYZ, float W)
	: Register(_mm_set_ps(W, InVectorXYZ.Z, InVectorXYZ.Y, InVectorXYZ.X))
{ }

FORCEINLINE
FVector4D::FVector4D(const FVector2D &InVectorXY, const FVector2D &InVectorZW)
	: Register(_mm_set_ps(InVectorZW.Y, InVectorZW.X, InVectorXY.Y, InVectorXY.X))
{ }

FORCEINLINE
FVector4D::FVector4D(const FVector2D &InVectorXY, float Z, float W)
	: Register(_mm_set_ps(W, Z, InVectorXY.Y, InVectorXY.X))
{ }

FORCEINLINE float &
FVector4D::operator[](uint32 Index)
{
	Assert(Index < 4);
	return (&X)[Index];
}

FORCEINLINE float 
FVector4D::operator[](uint32 Index) const
{
	Assert(Index < 4);
	return (&X)[Index];
}

FORCEINLINE FVector4D
FVector4D::operator-() const
{
	return _mm_xor_ps(Register, _mm_castsi128_ps(_mm_set1_epi32(0x80000000)));
}

FORCEINLINE FVector4D
FVector4D::operator+(float Value) const
{
	return _mm_add_ps(Register, _mm_set_ps(Value, Value, Value, Value));
}

FORCEINLINE FVector4D
FVector4D::operator+(const FVector4D &Other) const
{
	return _mm_add_ps(Register, Other.Register);
}

FORCEINLINE FVector4D
FVector4D::operator-(const FVector4D &Other) const
{
	return _mm_sub_ps(Register, Other.Register);
}

FORCEINLINE FVector4D
FVector4D::operator-(float Value) const
{
	return _mm_sub_ps(Register, _mm_set_ps(Value, Value, Value, Value));
}

FORCEINLINE FVector4D
FVector4D::operator*(const FVector4D &Other) const
{
	return _mm_mul_ps(Register, Other.Register);
}

FORCEINLINE FVector4D
FVector4D::operator*(float Value) const
{
	return _mm_mul_ps(Register, _mm_set_ps(Value, Value, Value, Value));
}

FORCEINLINE FVector4D
FVector4D::operator/(const FVector4D &Other) const
{
	return _mm_div_ps(Register, Other.Register);
}

FORCEINLINE FVector4D
FVector4D::operator/(float Value) const
{
	return _mm_div_ps(Register, _mm_set_ps(Value, Value, Value, Value));
}

FORCEINLINE FVector4D &
FVector4D::operator=(float Value)
{
	Register = _mm_set1_ps(Value);
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator=(const FVector4D &Other)
{
	Register = Other.Register;
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator+=(float Value)
{
	Register = _mm_add_ps(Register, _mm_set1_ps(Value));
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator+=(const FVector4D &Other)
{
	Register = _mm_add_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator-=(float Value)
{
	Register = _mm_sub_ps(Register, _mm_set1_ps(Value));
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator-=(const FVector4D &Other)
{
	Register = _mm_sub_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator*=(float Value)
{
	Register = _mm_mul_ps(Register, _mm_set1_ps(Value));
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator*=(const FVector4D &Other)
{
	Register = _mm_mul_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator/=(float Value)
{
	Register = _mm_div_ps(Register, _mm_set1_ps(Value));
	return *this;
}

FORCEINLINE FVector4D &
FVector4D::operator/=(const FVector4D &Other)
{
	Register = _mm_div_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE bool
FVector4D::operator==(const FVector4D &Other) const
{
	return ((_mm_movemask_ps(_mm_cmpeq_ps(Register, Other.Register))) & 0x07) == 0x07;
}

FORCEINLINE bool
FVector4D::operator!=(const FVector4D &Other) const
{
	return !(*this == Other);
}