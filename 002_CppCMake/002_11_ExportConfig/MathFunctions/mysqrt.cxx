#include "MathFunctions.h"

#include "Table.h"                                     // generated header by CMake


namespace math_functions
{
    namespace detail
    {
        double my_sqrt(double input_value)
        {
            if (input_value < 0)
            {
                std::cerr << "Error! Can't figure out the square root."
                          << "Your number less than zero."
                          << std::endl;

                return std::cerr.good() ? EXIT_SUCCESS : EXIT_FAILURE;
            }

            if (input_value == 0)
            {
                return 0;
            }

            if (input_value == 1)
            {
                return 1;
            }

            double result = input_value;

            if (    input_value >= 1
                 && input_value <  10
                )
            {
                std::cout << "Use the table to help find an initial value "
                      << std::endl;

                result = sqrt_table[static_cast<int> (input_value)];
            }

            for (int i = 0;
                     i < 10;
                     i++
                )
            {
                if (result <= 0)
                {
                    result = 0.001;
                }

                double delta = input_value - (result * result);

                result = result + delta / result * 0.5;
            }

            return result;
        }
    }
}