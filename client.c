/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:28:56 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/01/21 19:34:35 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include <stdlib.h>
#include <signal.h>

void send_msg(int pid, char* msg)
{
    int i;
    int j;
    int b;
    char c;

    i = 0;
    while(msg[i])
    {
        c = msg[i];
        j = 7;
        while(j >= 0)
        {
            b = c & (1u << j);
            if (b != 0)
            {
                if (kill(pid, SIGUSR2) == -1)
                    exit(2);
                    
            }
                
            else
            {
                if (kill(pid, SIGUSR1) == -1)
                    exit(2);
                    
            }
                
            j--;
            
            pause();
        }
        i++;
    }

}

void send_msg_len_bits(int pid, int msg_len)
{
    int i;
    int b;

        i = 31;
        while(i >= 0)
        {
            b = msg_len & (1u << i);
            if (b != 0)
            {
                if (kill(pid, SIGUSR2) == -1)
                    exit(2);
                    
            }
                
            else
            {
                if (kill(pid, SIGUSR1) == -1)
                    exit(2);
                    
            }
                
            i--;
            
            pause();
        }

}

void send_msg_len(int pid, char* msg){
    int msg_len;

    msg_len = ft_strlen(msg);
    send_msg_len_bits(pid, msg_len);
}

void handle_SIGUSR1(int signum)
{
	(void)signum;
}


int main (int argc, char ** argv)
{
	struct sigaction action_SIGUSR1;
    int pid;

    if (argc != 3 || !argv[1] || !argv[2] || ft_strlen(argv[2]) == 0)
    {
        ft_printf("Usage : %s <PID> <Message>\n", argv[0]);
        exit(1);
    }
    pid = ft_atoi(argv[1]);
    if (!pid)
    {
        ft_printf("Incorrect PID\nUsage : %s <PID> <Message>\n", argv[0]);
        exit(1);
    }
	
	action_SIGUSR1.sa_handler = handle_SIGUSR1;
	sigemptyset (&action_SIGUSR1.sa_mask);
	action_SIGUSR1.sa_flags = 0;

	sigaction (SIGUSR1, &action_SIGUSR1, NULL);

    send_msg_len(pid, argv[2]);
    send_msg(pid, argv[2]);
    
}
