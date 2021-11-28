#ifndef A7A79940_00FC_4806_887F_F4C67498E3C3
#define A7A79940_00FC_4806_887F_F4C67498E3C3

namespace pswd::charset::errors
{
    constexpr const char* g_uppercaseNotFound = "your password must have atleast one uppercase character.";
    constexpr const char* g_numericNotFound   = "your password must have atleast one numeric character.";
    constexpr const char* g_specialNotFound   = "your password must have atleast one special character.";
    constexpr const char* g_invalidPassSize   = "invalid password size.";
    constexpr const char* g_repeatedChars     = "your password have too many repetaed characters.";
    constexpr const char* g_sequencialChars   = "your password have too many sequencial characters.";

    inline double error_message(const std::string_view& error) 
    {
        std::cout << error << '\n'; return 0.0;
    }
}

#endif /* A7A79940_00FC_4806_887F_F4C67498E3C3 */
