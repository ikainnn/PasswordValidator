#ifndef AB61AB95_03E3_4195_B3FA_5D6F8F9CBF32
#define AB61AB95_03E3_4195_B3FA_5D6F8F9CBF32

#include <array>

#include "charset.hpp"

namespace pswd::charset 
{
    using CharSet = std::pair<std::vector<char>, std::string>;

    const CharSet g_charsetNumeric {
        { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' },
        pswd::charset::errors::g_numericNotFound};
    const CharSet g_charsetSpecial {
        { '!',  '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',
          '-',  '.', '/', ':', ';', '<',  '=', '>', '?', '@', '[',
          '\\', ']', '^', '_', '`', '{',  '|', '}', '~' },
        pswd::charset::errors::g_specialNotFound};
    const CharSet g_charsetUpper   {
        { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y' },
        pswd::charset::errors::g_uppercaseNotFound};

    const std::array<CharSet, 3> g_charsetPool {
        g_charsetNumeric, g_charsetSpecial, g_charsetUpper };
}

#endif /* AB61AB95_03E3_4195_B3FA_5D6F8F9CBF32 */
