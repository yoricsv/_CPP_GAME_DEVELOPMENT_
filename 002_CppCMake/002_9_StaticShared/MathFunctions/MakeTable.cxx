#include <cmath>

#include <fstream>
#include <iostream>

int main (int argc, char * argv[])
{
    // is enough arguments
    if (argc < 2)
    {
        return EXIT_FAILURE;
    }

    std::ofstream fout(
        argv[1],
        std::ios_base::out
    );

    const bool fileOpen = fout.is_open();

    if (fileOpen)
    {
        fout << "double sqrt_table[] = {"
             << std::endl;

        for (int i = 0;
                 i < 10;
                 i++
             )
        {
            fout << sqrt(static_cast<double>(i))
                 << ","
             << std::endl;
        }

        // close the table with a zero
        fout << "0};" << std::endl;

        fout.close();
    }

    return fileOpen ? EXIT_SUCCESS : EXIT_FAILURE;
}