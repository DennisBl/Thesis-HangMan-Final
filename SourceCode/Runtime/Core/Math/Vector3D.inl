FORCEINLINE
FVector3D::FVector3D()
	: Register(_mm_setzero_ps())
{ }

FORCEINLINE
FVector3D::FVector3D(const FVector3D &Other)
	: Register(Other.Register)
{ }

FORCEINLINE
FVector3D::FVector3D(float X, float Y, float Z)
	: Register(_mm_set_ps(0, Z, Y, X))
{ }

FORCEINLINE
FVector3D::FVector3D(const __m128 &Register)
	: Register(Register)
{ }

FORCEINLINE
FVector3D::FVector3D(float Value)
	: Register(_mm_set_ps(0, Value, Value, Value))
{ }

FORCEINLINE
FVector3D::FVector3D(const FVector4D &InVectorXYZ)
	: Register(_mm_set_ps(0, InVectorXYZ.Z, InVectorXYZ.Y, InVectorXYZ.X))
{ }

FORCEINLINE
FVector3D::FVector3D(const FVector2D &InVectorXY)
	: Register(_mm_set_ps(0, 0, InVectorXY.Y, InVectorXY.X))
{ }

FORCEINLINE
FVector3D::FVector3D(const FVector2D &InVectorXY, float Z)
	: Register(_mm_set_ps(0, Z, InVectorXY.Y, InVectorXY.X))
{ }

FORCEINLINE float 
FVector3D::GetLength() const
{
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Register, Register, 0x71)));
}

FORCEINLINE FVector3D 
FVector3D::GetNormalized() const
{
	return _mm_div_ps(Register, _mm_sqrt_ps(_mm_dp_ps(Register, Register, 0xFF)));
}

FORCEINLINE float &
FVector3D::operator[](uint32 Index)
{
	Assert(Index < 3);
	return (&X)[Index];
}

FORCEINLINE float 
FVector3D::operator[](uint32 Index) const
{
	Assert(Index < 3);
	return (&X)[Index];
}

FORCEINLINE FVector3D 
FVector3D::operator-() const
{
	return _mm_xor_ps(Register, _mm_castsi128_ps(_mm_set1_epi32(0x80000000)));
}

FORCEINLINE FVector3D
FVector3D::operator+(float Value) const
{
	return _mm_add_ps(Register, _mm_set_ps(0, Value, Value, Value));
}

FORCEINLINE FVector3D 
FVector3D::operator+(const FVector3D &Other) const
{
	return _mm_add_ps(Register, Other.Register);
}

FORCEINLINE FVector3D 
FVector3D::operator-(const FVector3D &Other) const
{
	return _mm_sub_ps(Register, Other.Register);
}

FORCEINLINE FVector3D
FVector3D::operator-(float Value) const
{
	return _mm_sub_ps(Register, _mm_set_ps(0, Value, Value, Value));
}

FORCEINLINE FVector3D
FVector3D::operator*(const FVector3D &Other) const
{
	return _mm_mul_ps(Register, Other.Register);
}

FORCEINLINE FVector3D
FVector3D::operator*(float Value) const
{
	return _mm_mul_ps(Register, _mm_set_ps(0, Value, Value, Value));
}

FORCEINLINE FVector3D 
FVector3D::operator/(const FVector3D &Other) const
{
	return _mm_div_ps(Register, Other.Register);
}

FORCEINLINE FVector3D 
FVector3D::operator/(float Value) const
{
	return _mm_div_ps(Register, _mm_set_ps(0, Value, Value, Value));
}

FORCEINLINE FVector3D &
FVector3D::operator=(float Value)
{
	Register = _mm_set_ps(0, Value, Value, Value);
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator=(const FVector3D &Other)
{
	Register = Other.Register;
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator+=(float Value)
{
	Register = _mm_add_ps(Register, _mm_set_ps(0, Value, Value, Value));
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator+=(const FVector3D &Other)
{
	Register = _mm_add_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator-=(float Value)
{
	Register = _mm_sub_ps(Register, _mm_set_ps(0, Value, Value, Value));
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator-=(const FVector3D &Other)
{
	Register = _mm_sub_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator*=(float Value)
{
	Register = _mm_mul_ps(Register, _mm_set_ps(0, Value, Value, Value));
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator*=(const FVector3D &Other)
{
	Register = _mm_mul_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator/=(float Value)
{
	Register = _mm_div_ps(Register, _mm_set_ps(0, Value, Value, Value));
	return *this;
}

FORCEINLINE FVector3D &
FVector3D::operator/=(const FVector3D &Other)
{
	Register = _mm_div_ps(Register, Other.Register);
	return *this;
}

FORCEINLINE bool 
FVector3D::operator==(const FVector3D &Other) const
{
	return ((_mm_movemask_ps(_mm_cmpeq_ps(Register, Other.Register))) & 0x07) == 0x07;
}

FORCEINLINE bool 
FVector3D::operator!=(const FVector3D &Other) const
{
	return !(*this == Other);
}

FORCEINLINE float
FVector3D::Dot(const FVector3D &InVectorA, const FVector3D &InVectorB)
{
	return _mm_cvtss_f32(_mm_dp_ps(InVectorA.Register, InVectorB.Register, 0x71));
}

FORCEINLINE FVector3D
FVector3D::Cross(const FVector3D &InVectorA, const FVector3D &InVectorB)
{
	return _mm_sub_ps(
		_mm_mul_ps(
			_mm_shuffle_ps(InVectorA.Register, InVectorA.Register, _MM_SHUFFLE(3, 0, 2, 1)),
			_mm_shuffle_ps(InVectorB.Register, InVectorB.Register, _MM_SHUFFLE(3, 1, 0, 2))),
		_mm_mul_ps(
			_mm_shuffle_ps(InVectorA.Register, InVectorA.Register, _MM_SHUFFLE(3, 1, 0, 2)),
			_mm_shuffle_ps(InVectorB.Register, InVectorB.Register, _MM_SHUFFLE(3, 0, 2, 1))));
}