#include "MathFunctions.h"

double my_sqrt(double input_value)
{
    double result;

#if defined(HAVE_LOG) && defined(HAVE_EXP)
   result = exp(log(input_value) * 0.5);

   std::cout << "Computing sqrt of " << input_value
             << " to be "            << result
             << " using log and exp"
             << std::endl;
#else
    if(input_value < 0)
    {
        std::cerr << "Error! Can't figure out the square root."
                  << "Your number less than zero."
                  << std::endl;

        return std::cerr.good() ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    if(input_value == 1)
    {
        return 1;
    }

    result = input_value / 2;

    while(std::abs(input_value - result * result ) >= 0.001)
    {
        result = ((input_value / result) + result) / 2;

        if(input_value == result * result)
        {
            return result;
        }
    }
#endif
    return result;
}