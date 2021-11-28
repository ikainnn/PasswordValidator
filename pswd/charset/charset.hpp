#ifndef A79329D4_667B_4891_BB3B_052F4C7CC173
#define A79329D4_667B_4891_BB3B_052F4C7CC173

namespace pswd::charset
{
    constexpr std::array<char, 10> g_numericCharset {
        '0', '1', '2',  '3', '4', '5',  '6', '7', '8', '9' };

    constexpr std::array<char, 26> g_upperCharset   {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    constexpr std::array<char, 32> g_specialCharset {
        '!', '"',  '#', '$', '%', '&', '\'', '(', ')', '*', '+',
        ',', '-',  '.', '/', ':', ';', '<',  '=', '>', '?', '@',
        '[', '\\', ']', '^', '_', '`', '{',  '|', '}', '~' };
}

#endif /* A79329D4_667B_4891_BB3B_052F4C7CC173 */
