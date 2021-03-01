#include "GameCharCodeMap.h"

const TArray<FCharCodeMap> GreekCharCodeMap =
{
    { 'A', 'A' },
    { 'B', 'B' },
    { 'C', 'Y' },
    { 'D', 'D' },
    { 'E', 'E' },
    { 'F', 'F' },
    { 'G', 'G' },
    { 'H', 'H' },
    { 'I', 'I' },
    { 'J', 'X' },
    { 'K', 'K' },
    { 'L', 'L' },
    { 'M', 'M' },
    { 'N', 'N' },
    { 'O', 'O' },
    { 'P', 'P' },
    { 'U', 'Q' },
    { 'R', 'R' },
    { 'S', 'S' },
    { 'T', 'T' },
    { 'V', 'W' },
    { 'X', 'C' },
    { 'Y', 'U' },
    { 'Z', 'Z' },
    { 'Q', 'Q' },
    { 'W', 'W' },
    { '0', '0' },
    { '1', '1' },
    { '2', '2' },
    { '3', '3' },
    { '4', '4' },
    { '5', '5' },
    { '6', '6' },
    { '7', '7' },
    { '8', '8' },
    { '9', '9' },
};

static const TArray<TCHAR> GreekCharCodeExceptions =
{
    'Q', 'W',
};

static FGameCharCodeMap FGameCharCodeMapGlobal;

FGameCharCodeMap *
FGameCharCodeMap::Get()
{
    return &FGameCharCodeMapGlobal;
}

void
FGameCharCodeMap::SetGameLanguage(EGameLanguage InGameLanguage)
{
    GameLanguage = InGameLanguage;
}

bool 
FGameCharCodeMap::IsCharCodePresent(const FCharCodeMap &CharCodeMap)
{
    switch(GameLanguage)
    {
    case GL_English:
        return CharCodeMap.CharCode;
        break;
    case GL_Greek:
        return !GreekCharCodeExceptions.Contains(CharCodeMap.KeyCode);
        break;
    }

    return false;
}

TCHAR 
FGameCharCodeMap::GetMappedCharCode(const FCharCodeMap &CharCodeMap)
{   
    switch(GameLanguage)
    {
    case GL_English:
        return CharCodeMap.KeyCode;
        break;
    case GL_Greek:
        return CharCodeMap.CharCode;
        break;
    }

    return 0;
}

TCHAR
FGameCharCodeMap::GetMappedCharCodes(const TCHAR& Letter)
{   
    for (uint32 Index = 0; Index < GreekCharCodeMap.GetCapacity(); Index++)
    {
        if (GreekCharCodeMap[Index].KeyCode == Letter)
        {
            return GreekCharCodeMap[Index].CharCode;
        }
    }
    return 0;
}