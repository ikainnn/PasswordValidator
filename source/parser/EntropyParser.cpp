#include "EntropyParser.hpp"

#include <cmath>
#include <numeric>

namespace pswd::parser
{
    std::string_view parse_password_entropy(float passwordEntropy)
    {
        switch (static_cast<std::int32_t>(std::floor(passwordEntropy))) 
        {
            case std::numeric_limits<std::int32_t>::min() ... 00:
                return "are you even trying?";
            
            case 01 ... 20: return "very weak";
            case 21 ... 40: return "weak";
            case 41 ... 50: return "decent";
            case 51 ... 60: return "strong";
            
            case 61 ... std::numeric_limits<std::int32_t>::max():
                return "very strong";
        }

        return "???";
    }
}