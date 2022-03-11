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
    
    bool validate_password_length(std::string_view password);
    bool validate_password_ordering(std::string_view password);
    bool validate_password_symbols(std::string_view password);

    template <class T> inline bool validate_password(T&& password)
    {
        return validate_password_length(std::forward<T>(password)) && 
               validate_password_ordering(std::forward<T>(password)) && 
               validate_password_symbols(std::forward<T>(password));
    }
}

#endif