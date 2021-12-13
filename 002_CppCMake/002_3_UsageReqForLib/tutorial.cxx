#include <iostream>

#include "TutorialConfig.h"

#ifdef USE_MY_MATH
    #include "MathFunctions.h"
#endif

double input_value;

int main (int argc, char * argv[])
{
    if (argc < 2)
    {
        std::cout << argv[0]
                  << " Version "    << Tutorial_VERSION_MAJOR
                  << "."            << Tutorial_VERSION_MINOR
            << std::endl;
    }

    std::cout << "Enter a number: ";
    std::cin  >> input_value;

#ifdef USE_MYMATH
    const double result = mysqrt(input_value);
#else
    const double result = sqrt(input_value);
#endif

    std::cout   << "The sqrt of "   << input_value
                << " is "           << result
            << std::endl;

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}