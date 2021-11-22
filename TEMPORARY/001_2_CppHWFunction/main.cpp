#include <unistd.h>

static const     int  BUFFER_SIZE = 10000U;
       constexpr auto word        = "Hello, world!\n";

static const char * buffer[BUFFER_SIZE];

int prints(const char * buffer, int size)
{
    int exit_code = 0;

    while(buffer)
    int i;
    for(i=0; i < strlen(buffer); i++)
            putc(buffer[i]);

    return exit_code;
}

void gets(buffer)
{
    while( (*buffer = getc()) != '\r')
    {
        putc(*buffer++);
    }

    *buffer = '\0';
}



void printc(ip) unsigned long
{
        putc(ip);
}
int printd(ip) unsigned long
{
        if(ip < 0)
        {
                putc('-');
                ip = -ip;
        }
 if(ip == 0)
 {
  putc('0');
  return 0;
 }
 rpi(ip, 10);
}
void printx(ip) unsigned long
{
        prints("0x"); //PUT OR OUTPUT LOOK LIKE INT
        rpi(ip, 16);
}
int printl(ip) unsigned long;
{
 if(ip == 0)
 {
  putc('0');
  return 0;
 }
        rpi(ip, 10);
        putc('L');
}

char *fmt;
void printf(fmt)
{
    char *cp;               //POINTER TO LOOP THROUGH
    unsigned long *ip;     //POINTER FOR

    cp = fmt;               //SET POINTER TO START POINTER {FMT}
    ip = &fmt+1;            //Board says &fmt:but will not work without +1

    while(*cp)
    {
        //IF C != %
        if(*cp != '%')
        {
            printf("%c", *cp);
            if(*cp == '\n')
            {
                    //putc('\n'); //implied
                    putc('\r');
            }
            cp++;
            continue; //NEXT CHAR
        }
        else
        {
            //MOVE ONE CHARACTER (%{x}) SO WE CAN GET x
            cp++;
            switch(*cp)
            {
                case 'c':
                        printc(*ip);
                        break;
                case 's':
                        prints(*ip);
                        break;
                case 'd':
                        printd(*ip);
                        break;
                case 'x':
                        printx(*ip);
                        break;
                case 'l':
                        printl(*ip);
                        break;
                default:
                        break;
            }
        }
        cp++;
        ip++;
    }
}
//int print(const char* str, int size)
//{
//    int exit_code = 0;

//    syscall(, 1, str, size);
//    return exit_code;
//}



int main(int argc, char *argv[])
{

    print(word, 14);

//    return printf(word) < 0 ? EXIT_SUCCESS : EXIT_FAILURE;//2

//    std::cout << "Hello world!" << std::endl; //1
//    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE; //1
}
