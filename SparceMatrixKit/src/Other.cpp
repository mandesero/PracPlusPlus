#include "Other.h"

bool startsWithHash(const std::string &input)
{
    auto nonSpaceChar = std::find_if(input.begin(), input.end(), [](char c)
                                     { return !std::isspace(c); });

    if (nonSpaceChar != input.end() && *nonSpaceChar == '#')
        return true;

    return false;
}
