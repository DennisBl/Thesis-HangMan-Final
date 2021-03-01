#ifndef GAME_CHAR_CODE_MAP_H
#define GAME_CHAR_CODE_MAP_H

#include <CoreMinimal.h>

enum EGameLanguage
{
    GL_English,
    GL_Greek,
};

struct FCharCodeMap
{
    TCHAR KeyCode;
    TCHAR CharCode;
};

extern const TArray<FCharCodeMap> GreekCharCodeMap;

class FGameCharCodeMap
{
public:
    static FGameCharCodeMap *Get();

    void SetGameLanguage(EGameLanguage InGameLanguage);
    bool IsCharCodePresent(const FCharCodeMap &CharCodeMap);
    TCHAR GetMappedCharCode(const FCharCodeMap &CharCodeMap);
    TCHAR GetMappedCharCodes(const TCHAR &Letter);


private:
    EGameLanguage GameLanguage;
};

#endif