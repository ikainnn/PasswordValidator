#ifndef SECURITY_HPP
#define SECURITY_HPP

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>

#include "../timing.hpp"
#include "charset/charset.hpp"

namespace pswd
{
    extern const std::size_t g_minLength;
    extern const std::size_t g_maxLength;
    
    std::string_view parse_entropy(std::float_t entropy);
    std::double_t validate_password(const std::string_view& password);
}

#endif
