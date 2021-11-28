#include "security.hpp"

namespace pswd
{    
    static std::int32_t error_message(const std::string_view& error) 
    {
        std::cout << error << '\n'; return 0.0;
    }

    static std::double_t calc_password_entropy(const std::size_t passwordSize) 
    {
        auto charsetSize = pswd::charset::g_upperCharset.size() +
                           pswd::charset::g_numericCharset.size() +
                           pswd::charset::g_specialCharset.size();

        // source: https://generatepasswords.org/how-to-calculate-entropy/
        return std::log2(std::pow(charsetSize, passwordSize));
    }
    
    template <std::size_t SZ>
    static bool search_charset_chars(const std::string_view& password, const std::array<char, SZ>& charset)
    {
        auto result = std::find_if(
            password.begin(), password.end(), [&charset](const auto& currentChar) {       
                return std::find(charset.begin(), charset.end(), currentChar) != charset.end();
            });
        return result != password.end();
    }

    static bool search_charset_chars(const std::string_view& password)
    {
        // checks if the password contains uppercase chars
        if (!search_charset_chars(password, pswd::charset::g_upperCharset))
            return error_message("your password must contain atleast one uppercase character.");

        // checks if the password contains numeric chars
        if (!search_charset_chars(password, pswd::charset::g_numericCharset))
            return error_message("your password must contain atleast one one digit.");

        // checks if the password contains special chars
        if (!search_charset_chars(password, pswd::charset::g_specialCharset))
            return error_message("your password must contain atleast one symbol.");
        
        return true;
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
            return error_message("invalid password size.");
        
        // checks if the password contains characters from the charset.  ie: 0, A, [...
        if (!search_charset_chars(password))
            return 0;
        
        // checks if the password has more than 2 repeated characters.   ie: FFF...
        if (search_repeated_chars(password) > 2)
            return error_message("your password has too many repeated characters.");

        // checks if the password has more than 4 sequencial characters. ie: abcde...   
        if (search_sequencial_chars(password) > 4)
            return error_message("your password has too many sequencial characters.");

        return calc_password_entropy(password.size());
    }
}