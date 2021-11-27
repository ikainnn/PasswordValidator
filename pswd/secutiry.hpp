#ifndef A7A114CC_D30E_4D73_B48F_924481B695B7
#define A7A114CC_D30E_4D73_B48F_924481B695B7

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

namespace pswd
{
    extern const std::size_t g_minLength;
    extern const std::size_t g_maxLength;
    
    std::string_view parse_entropy(std::double_t entropy);
    std::double_t validate_password(const std::string_view& password);
}

#endif /* A7A114CC_D30E_4D73_B48F_924481B695B7 */
