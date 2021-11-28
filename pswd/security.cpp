#include "security.hpp"

namespace pswd
{    
    constexpr static std::double_t calc_password_entropy(const std::size_t passwordSize) 
    {
        // source: https://generatepasswords.org/how-to-calculate-entropy/

        auto charsetSize = []() -> std::size_t {
            auto result = std::accumulate(pswd::charset::g_charsetPool.begin(), pswd::charset::g_charsetPool.end(), 1, 
                [](auto count, const auto& elem) {
                    return elem.first.size();
                });
            return result;
        }();

        return std::log2(std::pow(charsetSize, passwordSize));
    }
    
    constexpr static bool search_charset_chars(const std::string_view& password, const std::vector<char>& charset)
    {
        auto result = std::find_if(
            password.begin(), password.end(), [&charset](const auto& currentChar) {
                return std::find(charset.begin(), charset.end(),currentChar) != charset.end();
            });
        return result != password.end();
    }
    
    constexpr static std::int32_t search_repeated_chars(const std::string_view& password)
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
    
    constexpr static std::int32_t search_sequencial_chars(const std::string_view& password) 
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
            return pswd::charset::errors::error_message(pswd::charset::errors::g_invalidPassSize);
        
        // checks if the password contains characters from the charset.
        for (const auto&[charset, message] : pswd::charset::g_charsetPool) {
            if (!search_charset_chars(password, charset))
                return pswd::charset::errors::error_message(message);
        }

        if      (search_repeated_chars(password)   > 2) 
            return pswd::charset::errors::error_message(pswd::charset::errors::g_repeatedChars);
        else if (search_sequencial_chars(password) > 4)
            return pswd::charset::errors::error_message(pswd::charset::errors::g_sequencialChars);

        return calc_password_entropy(password.size());
    }
}