#ifndef ENTROPYPARSER_HPP
#define ENTROPYPARSER_HPP

#include <string_view>

namespace pswd::parser
{
    /**
     * Given an entropy value, return a string that describes the strength of the password
     * 
     * @param passwordEntropy The entropy of the password.
     * 
     * @return A string represeting the entropy.
     */
    std::string_view parse_password_entropy(float passwordEntropy);
}

#endif