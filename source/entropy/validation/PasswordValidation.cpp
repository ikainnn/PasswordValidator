#include "PasswordValidation.hpp"

#include <spdlog/spdlog-inl.h>

#include <algorithm>
#include <string_view>

namespace pswd::entropy::validation
{
    constexpr auto g_minSize = 6;
    constexpr auto g_maxSize = 24;

    bool validate_password_length(std::string_view password)
    {
        if (!(password.size() >= g_minSize && password.size() <= g_maxSize))
        {
            spdlog::error("invalid password size. your password should be between {} to {} characters long.", g_minSize, g_maxSize);
            return false;
        }

        return true;
    }

    bool validate_password_ordering(std::string_view password)
    {
        for (auto iterator = password.begin(); *iterator; ++iterator)
        {
            const auto previousIterator = std::prev(iterator);
            const auto adjacentIterator = std::next(iterator);

            if (*previousIterator == *iterator || *adjacentIterator == *iterator)
            {
                spdlog::error("your password must not contain repeated ordering."); return false;
            }
            else if (*previousIterator == *iterator-1 || *adjacentIterator == *iterator+1)
            {
                spdlog::error("your password must not contain sequential ordering."); return false;
            }
        }

        return true;
    }

    bool validate_password_symbols(std::string_view password)
    {
        constexpr static auto c_genericTreshold = 2;

        auto searchCharacter = [](auto password, auto checkingPredicate)
        {
            auto result = std::count_if(password.begin(), password.end(), [&checkingPredicate](char _c)
            { 
                return checkingPredicate(_c); 
            });

            return result >= c_genericTreshold;
        };

        if (!searchCharacter(password, isdigit))
        {
            spdlog::error("your password must contain atleast {} numeric digits.", c_genericTreshold); return false;
        }
        else if (!searchCharacter(password, isupper))
        {
            spdlog::error("your password must contain atleast {} uppercase letters.", c_genericTreshold); return false;
        }
        else if (!searchCharacter(password, ispunct))
        {
            spdlog::error("your password must contain atleast {} special symbols.", c_genericTreshold); return false;
        }

        return true;
    }
}