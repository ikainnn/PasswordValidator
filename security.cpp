#include "secutiry.hpp"

namespace pswd
{
    // ascii table characters. in total we have a charset pool of size 30
    static constexpr char g_upperCaseA          = 65, g_upperCaseZ        = 90,
                          g_numericZero         = 48, g_numericNine       = 57,
                          g_specialCharsBegin_1 = 33, g_specialCharsEnd_1 = 47, 
                          g_specialCharsBegin_2 = 58, g_specialCharsEnd_2 = 64;

    static double error_message(const std::string_view& error)
    {
        std::cout << error; return 0.0;
    }
    
    static std::double_t calc_password_entropy(const std::size_t passwordSize) 
    {
        // source: https://generatepasswords.org/how-to-calculate-entropy/
        return std::log2(std::pow(2*26 + 30, passwordSize));
    }
    
    static bool search_chars_between(const std::string_view& password, char start, char end)
    {
        auto result = std::find_if(
            password.begin(), password.end(), [start, end](const auto character) {
                return character >= start && character <= end;
            });
        return result != password.end();
    }
    
    static std::int32_t search_repeated_chars(const std::string_view& password)
    {
        auto result = std::accumulate(
            password.begin(), password.end(), 0, [](auto count, const auto& currentChar) {
                static char lastSeenChar;
                if(currentChar == lastSeenChar)
                    ++count;
                lastSeenChar = currentChar;

                return count;
            });

        return result;
    }
    
    static std::int32_t search_sequencial_chars(const std::string_view& password) 
    {
        auto result = std::accumulate(
            password.begin(), password.end(), 0, [](auto count, const auto& currentChar) {
                static char lastSeenChar;
                if (currentChar == lastSeenChar + 1 || currentChar == lastSeenChar - 1)
                    ++count;
                lastSeenChar = currentChar;

                return count;
            });

        return result;
    }
    
    std::string_view parse_entropy(std::double_t entropy)
    {
        if      (entropy <= 0.0f)
            return "are you even trying?";
        else if (entropy >= 0.0f  && entropy <= 20.0f)
            return "very weak";
        else if (entropy >= 20.0f && entropy <= 40.0f)
            return "weak";
        else if (entropy >= 40.0f && entropy <= 50.0f)
            return "decent";
        else if (entropy >= 50.0f && entropy <= 60.0f)
            return "strong";
        else if (entropy >= 60.0f)
            return "very strong";
        
        return "???";
    }

    std::double_t validate_password(const std::string_view& password)
    {
        // challenge constraint.
        if (password.size() < g_minLength || password.size() > g_maxLength)
            return error_message("invalid password size.\n");

        // tries to find for uppercase characters in the password.
        if (!search_chars_between(password, g_upperCaseA, g_upperCaseZ))
            return error_message("password must contain an uppercase character.\n");
        
        // tries to find for numeric digits in the password.
        if (!search_chars_between(password, g_numericZero, g_numericNine))
            return error_message("password must contain a number.\n");

        // will search for special characters in the password.
        if (!(search_chars_between(password, g_specialCharsBegin_1, g_specialCharsEnd_1) ||
              search_chars_between(password, g_specialCharsBegin_2, g_specialCharsEnd_2))) 
            return error_message("password must contain a special character.\n");

        // search for repeated chars in sequence
        if (search_repeated_chars(password) >= 2) 
            return error_message("too many repeated characters.\n");
        
        // will search for sequencial characters
        if (search_sequencial_chars(password) >= 4)
            return error_message("too many sequencial characters.\n");

        return calc_password_entropy(password.size());
    }
}