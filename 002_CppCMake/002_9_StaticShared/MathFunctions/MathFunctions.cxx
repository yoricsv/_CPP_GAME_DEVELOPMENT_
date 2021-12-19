#include "MathFunctions.h"

#include <cmath>

#ifdef USE_MY_MATH
    #include "mysqrt.h"
#endif

namespace math_functions
{
    double sqrt(double input_value)
    {
#ifdef USE_MY_MATH
        return detail::my_sqrt(input_value);
#else
        return std::sqrt(input_value);
#endif
    }
}