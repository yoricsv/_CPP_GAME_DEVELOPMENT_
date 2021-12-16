#include <cmath>
#include <cstdio>
#include <cstdlib>

int main (int argc, char *argv[])
{
    int    i;
    double result;

    // make sure we have enough arguments
    if (argc < 2)
    {
        return 1;
    }

    // open the output file
    FILE * ptrFile =
        fopen(
            argv[1],
            "w"
        );

    if (!ptrFile)
    {
        perror("Error! Can't open the file: ");
        return EXIT_FAILURE;
    }

    // create a source file with a table of square roots
    fprintf(
        ptrFile,
        "double sqrtTable[] = {\n"
    );

    for (   i = 0;
            i < 10;
            i++
        )
    {
        result = sqrt(static_cast<double> (i));

        fprintf(
            ptrFile,
            "%g,\n",
            result
        );
    }

    // close the table with a zero
    fprintf(
        ptrFile,
        "0};\n"
    );

    fclose(ptrFile);

    return EXIT_SUCCESS;
}