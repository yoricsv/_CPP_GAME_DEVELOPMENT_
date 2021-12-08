#include "main.h"

int main(int argc, char * argv[])
{
#ifdef USE_GET_LENGTH_FUNCTION
    int exit_code = print(word);
#else
    int exit_code = print(word, 14);
#endif

    return
#ifdef USE_GET_LENGTH_FUNCTION
           exit_code == -1
        || exit_code != getStringLength(word) ?
#else
           exit_code == -1 ?
#endif
                EXIT_FAILURE : EXIT_SUCCESS;
}

