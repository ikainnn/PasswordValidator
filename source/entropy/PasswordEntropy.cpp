#include "PasswordEntropy.hpp"

#include <cmath>

#include "validation/PasswordValidation.hpp"

namespace pswd::entropy
{
    float calculate_password_entropy(std::string_view password)
    {
        if (!validation::validate_password(password)) { return 0; }

        constexpr static auto c_availableCharacters = 93;

        // reference: https://generatepasswords.org/how-to-calculate-entropy/
        return static_cast<float>(std::log2(std::pow(c_availableCharacters, password.size())));
    }
}