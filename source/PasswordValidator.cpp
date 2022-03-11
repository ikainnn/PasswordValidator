#include <fmt/format.h>

#include <iostream>

#include "entropy/PasswordEntropy.hpp"
#include "parser/EntropyParser.hpp"

std::string get_user_password();

std::int32_t main()
{
    constexpr static std::string_view c_messageFormat = "Your password entropy has a value of {}, which is considered {}.\n";

    const auto password = get_user_password();
    const auto passwordEntropy = pswd::entropy::calculate_password_entropy(password);

    if (passwordEntropy)
    {
        fmt::print(c_messageFormat, passwordEntropy, pswd::parser::parse_password_entropy(passwordEntropy));
    }
}

std::string get_user_password()
{
    fmt::print("Please, enter your password:\n");

    std::string _ret; 
    std::getline(std::cin, _ret);
    
    return _ret;
}