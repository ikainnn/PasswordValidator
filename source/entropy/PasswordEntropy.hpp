
#ifndef PASSWORDENTROPY_HPP
#define PASSWORDENTROPY_HPP

#include <string_view>

namespace pswd::entropy
{
    /**
     * Calculate the entropy of a password
     * 
     * @param password The password to calculate the entropy for.
     * 
     * @return A floating value representing the entropy value.
     */
    float calculate_password_entropy(std::string_view password);
};

#endif