//----------------------------------------------------------------------------------------------------
// StringUtils.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Engine/Core/StringUtils.hpp"

#include <algorithm>
#include <cstdarg>

//----------------------------------------------------------------------------------------------------
int constexpr STRINGF_STACK_LOCAL_TEMP_LENGTH = 2048;

//----------------------------------------------------------------------------------------------------
String const Stringf(char const* format, ...)
{
    char    textLiteral[STRINGF_STACK_LOCAL_TEMP_LENGTH];
    va_list variableArgumentList;

    va_start(variableArgumentList, format);
    (void)vsnprintf_s(textLiteral, STRINGF_STACK_LOCAL_TEMP_LENGTH, _TRUNCATE, format, variableArgumentList);
    va_end(variableArgumentList);

    textLiteral[STRINGF_STACK_LOCAL_TEMP_LENGTH - 1] = '\0';    // In case vsnprintf overran (doesn't auto-terminate)

    return String(textLiteral);
}

//----------------------------------------------------------------------------------------------------
String const Stringf(int const   maxLength,
                     char const* format, ...)
{
    char  textLiteralSmall[STRINGF_STACK_LOCAL_TEMP_LENGTH];
    char* textLiteral = textLiteralSmall;

    if (maxLength > STRINGF_STACK_LOCAL_TEMP_LENGTH)
    {
        textLiteral = new char[maxLength];
    }

    va_list variableArgumentList;

    va_start(variableArgumentList, format);
    (void)vsnprintf_s(textLiteral, maxLength, _TRUNCATE, format, variableArgumentList);
    va_end(variableArgumentList);

    textLiteral[maxLength - 1] = '\0';      // In case vsnprintf overran (doesn't auto-terminate)

    String returnValue(textLiteral);

    if (maxLength > STRINGF_STACK_LOCAL_TEMP_LENGTH)
    {
        delete[] textLiteral;
    }

    return returnValue;
}

//----------------------------------------------------------------------------------------------------
StringList const SplitStringOnDelimiter(String const& originalString,
                                        char const    delimiterToSplitOn)
{
    StringList result;
    size_t     start = 0;
    size_t     end   = originalString.find(delimiterToSplitOn);     // Position of the first character of the found substring or npos if no such substring is found.

    // 1. If originalString is empty, store an empty string, and return.
    if (originalString.empty())
    {
        result.emplace_back("");

        return result;
    }

    // 2. While the end position is not the end ( npos ), keep storing string in the result stringList.
    while (end != String::npos)
    {
        // Store string base on the start and end in the originalString.
        result.push_back(String(originalString.substr(start, end - start)));

        // Move start position past the delimiter, and move end position to the next delimiterToSplitOn.
        start = end + 1;
        end   = originalString.find(delimiterToSplitOn, start);
    }

    // 3. Store the last substring of originalString (or the full string if no delimiter was found).
    result.emplace_back(originalString.substr(start));

    return result;
}

int SplitStringIntoLines(StringList& resultStringVector, String const& originalString)
{
    resultStringVector.clear();
    size_t findRes;
    size_t firstPos = 0;
    do
    {
        findRes                = originalString.find_first_of('\n', firstPos);
        std::string strSplited = originalString.substr(firstPos, findRes - firstPos);
        strSplited.erase(remove(strSplited.begin(), strSplited.end(), '\r'), strSplited.end());
        resultStringVector.push_back(strSplited);
        firstPos = findRes + 1;
    }
    while (findRes != std::string::npos);

    return (int)resultStringVector.size();
}

int SplitStringOnDelimiter( StringList& resultStringVector, std::string const& originalString, char delimiterToSplitOn, bool removeExtraSpace )
{
    resultStringVector.clear();

    size_t findRes;
    size_t firstPos = 0;
    do {
        findRes = originalString.find_first_of( delimiterToSplitOn, firstPos );
        std::string strSplited = originalString.substr( firstPos, findRes - firstPos );
        if (removeExtraSpace && findRes != std::string::npos) {
            size_t nextNoSpacePos = originalString.find_first_not_of( ' ', findRes + 1 );
            if (nextNoSpacePos != 0 && nextNoSpacePos != std::string::npos) {
                firstPos = nextNoSpacePos;
            }
            else if (nextNoSpacePos == std::string::npos) {
                findRes = std::string::npos;
            }
            else {
                firstPos = findRes + 1;
            }
            strSplited.erase( remove( strSplited.begin(), strSplited.end(), ' ' ), strSplited.end() );
        }
        else {
            firstPos = findRes + 1;
        }

        resultStringVector.push_back( strSplited );
    } while (findRes != std::string::npos);

    return (int)resultStringVector.size();

}
