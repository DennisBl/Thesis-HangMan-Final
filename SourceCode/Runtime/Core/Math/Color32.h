#ifndef COLOR32_H
#define COLOR32_H

#include <CommonTypes.h>
#include <Definitions.h>

class FColor32
{
public:
	union
	{
		struct
		{
			uint8 R;
			uint8 G;
			uint8 B;
			uint8 A;
		};

		uint16 HexCode;
	};

	static const int32 Black       = 0x000000FF;
	static const int32 White       = 0xFFFFFFFF;
	static const int32 Red         = 0xFF0000FF;
	static const int32 Lime        = 0x00FF00FF;
	static const int32 Blue        = 0x0000FFFF;
	static const int32 Yellow      = 0xFFFF00FF;
	static const int32 Cyan        = 0x00FFFFFF;
	static const int32 Magenta     = 0xFF00FFFF;
	static const int32 Silver      = 0xC0C0C0FF;
	static const int32 Gray        = 0x808080FF;
	static const int32 Maroon      = 0x192000FF;
	static const int32 Olive       = 0x801920FF;
	static const int32 Green       = 0x00FF00FF;
	static const int32 Purple      = 0x192008FF;
	static const int32 Teal        = 0x008080FF;
	static const int32 Navy        = 0x000080FF;
	static const int32 Orange      = 0xFF9600FF;
	static const int32 Translucent = 0x00000000;

public:
	FORCEINLINE FColor32();
	FORCEINLINE FColor32(uint32 Hex);
	FORCEINLINE FColor32(uint8 R, uint8 G, uint8 B);
	FORCEINLINE FColor32(uint8 R, uint8 G, uint8 B, uint8 A);
	FORCEINLINE FColor32(const FColor32 &InColor, uint8 A);

	FORCEINLINE bool IsOpaqueAlpha() const;
	FORCEINLINE bool IsZeroAlpha() const;

	FORCEINLINE bool operator ==(const FColor32 &Other) const;
	FORCEINLINE bool operator !=(const FColor32 &Other) const;
};

#include "Color32.inl"

#endif