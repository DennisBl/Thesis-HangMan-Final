FORCEINLINE
FColor32::FColor32()
	: R(0)
	, G(0)
	, B(0)
	, A(0)
{ }

FORCEINLINE
FColor32::FColor32(uint8 R, uint8 G, uint8 B)
	: R(R)
	, G(G)
	, B(B)
	, A(0xFF)
{ }

FORCEINLINE
FColor32::FColor32(uint8 R, uint8 G, uint8 B, uint8 A)
	: R(R)
	, G(G)
	, B(B)
	, A(A)
{ }

FORCEINLINE
FColor32::FColor32(uint32 Hex)
	: R((Hex & 0xFF000000) >> 24)
	, G((Hex & 0xFF0000) >> 16)
	, B((Hex & 0xFF00) >> 8)
	, A((Hex & 0xFF))
{ }

FORCEINLINE
FColor32::FColor32(const FColor32 &InColor, uint8 A)
	: R(InColor.R)
	, G(InColor.G)
	, B(InColor.B)
	, A(A)
{ }

FORCEINLINE bool
FColor32::IsOpaqueAlpha() const
{
	return A == 255;
}


FORCEINLINE bool
FColor32::IsZeroAlpha() const
{
	return A == 0;
}


FORCEINLINE bool 
FColor32::operator ==(const FColor32 &Other) const
{
	return HexCode == Other.HexCode;
}

FORCEINLINE bool 
FColor32::operator !=(const FColor32 &Other) const
{
	return !(*this == Other);
}