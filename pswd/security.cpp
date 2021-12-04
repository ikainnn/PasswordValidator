#include "security.hpp"

namespace pswd
{    
    static bool error_message(const std::string_view& error) 
    {
        std::cout << error << '\n'; return false;
    }

    static std::float_t calc_password_entropy(const std::size_t passwordSize) 
    {
        // source: https://generatepasswords.org/how-to-calculate-entropy/
        return static_cast<std::float_t>(std::log2(std::pow(35 + pswd::charset::g_specialCharset.size(), passwordSize)));
    }

    static std::int32_t search_repeated_chars(const std::string_view& password)
    {
        // auto timerBegin = TIMER_START();

        auto result = std::accumulate(
            password.begin(), password.end(), 0, [](auto count, const auto& currentChar) {
                static char lastSeenChar;
                if(currentChar == lastSeenChar)
                    ++count;
                lastSeenChar = currentChar;
                return count;
            });

        // TIMER_STOP(timerBegin);

        return result;
    }
    
    static std::int32_t search_sequencial_chars(const std::string_view& password) 
    {
        // auto timerBegin = TIMER_START();

        auto result = std::accumulate(
            password.begin(), password.end(), 0, [](auto count, const auto& currentChar) {
                static char lastSeenChar;
                if (currentChar == lastSeenChar + 1 || currentChar == lastSeenChar - 1)
                    ++count;
                lastSeenChar = currentChar;
                return count;
            });
        
        // TIMER_STOP(timerBegin);

        return result;
    }

    static bool search_charset_chars(const std::string_view& password)
    {
        // auto timerBegin = TIMER_START();

        bool numbrFlag = false, upperFlag = false, specialFlag = false;
        for (const auto currentChar : password) {
            if (!(numbrFlag && upperFlag && specialFlag)) {
                if (!numbrFlag) numbrFlag = std::isdigit(currentChar);
                if (!upperFlag) upperFlag = std::isupper(currentChar);
                if (!specialFlag) {
                    auto result = std::find(pswd::charset::g_specialCharset.begin(), 
                                            pswd::charset::g_specialCharset.end(), currentChar);
                    specialFlag = result != pswd::charset::g_specialCharset.end();
                }
            } else { break; }
        }

        // checks if the password contains uppercase chars
        if (!upperFlag)   return error_message("your password must contain atleast one uppercase character.");
        // checks if the password contains numeric chars
        if (!numbrFlag)   return error_message("your password must contain atleast one one digit.");
        // checks if the password contains special chars
        if (!specialFlag) return error_message("your password must contain atleast one symbol.");

        // TIMER_STOP(timerBegin);
        
        return numbrFlag && upperFlag && specialFlag;
    }

    std::string_view parse_entropy(std::float_t entropy)
    {
        switch (static_cast<std::int32_t>(entropy)) {
            case std::numeric_limits<std::int32_t>::min() ... 00:
                return "are you even trying?";
            case 01 ... 20:
                return "very weak";
            case 21 ... 40:
                return "weak";
            case 41 ... 50:
                return "decent";
            case 51 ... 60:
                return "strong";
            case 61 ... std::numeric_limits<std::int32_t>::max():
                return "very strong";
        }
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
