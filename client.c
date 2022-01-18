#include "ft_printf/includes/ft_printf.h"
#include <stdlib.h>

void send_msg(char* msg)
{
    int i;
    int b;
    char c;

    c = 'z';
    i = 7;
    while(i >= 0)
    {
        b = c & (1u << i);
        if (b != 0)
            ft_printf("1");
        else
            ft_printf("0");
        i--;
    }
}

int main (int argc, char ** argv)
{
    if (argc != 3 || !argv[1] || !argv[2])
    {
        ft_printf("Usage : %s <PID> <Message>", argv[0]);
        exit(1);
    }
    send_msg(argv[2]);
    
}
