#ifndef PASSWORDVALIDATION_HPP
#define PASSWORDVALIDATION_HPP

#include <string_view>

namespace pswd::entropy::validation
{
    /**
     * The function checks if the password contains atleast 2 digits, 2 uppercase letters and 2 special
     * symbols
     * 
     * @param password The password to be validated.
     * 
     * @return True if the password is a valid password, or false if it isnt.
     */
    bool validate_password(std::string_view password);
}

#endif