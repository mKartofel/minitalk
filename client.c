/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:28:56 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/01/21 10:33:59 by vfiszbin         ###   ########.fr       */
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
        //ft_printf("sent= ");
        while(j >= 0)
        {
            b = c & (1u << j);
            if (b != 0)
            {
                kill(pid, SIGUSR2);
                //ft_printf("1");
            }
                
            else
            {
                kill(pid, SIGUSR1);
                //ft_printf("0");
            }
                
            j--;
            
            pause();
        }
        i++;
    }

}

void handle_SIGUSR1(int signum)
{
	(void)signum;
}


int main (int argc, char ** argv)
{
    if (argc != 3 || !argv[1] || !argv[2] || ft_strlen(argv[2]) == 0)
    {
        ft_printf("Usage : %s <PID> <Message>\n", argv[0]);
        exit(1);
    }
	struct sigaction action_SIGUSR1;
	
	action_SIGUSR1.sa_handler = handle_SIGUSR1;
	sigemptyset (&action_SIGUSR1.sa_mask);
	action_SIGUSR1.sa_flags = 0;

	sigaction (SIGUSR1, &action_SIGUSR1, NULL);
	
	int pid = ft_atoi(argv[1]);
    send_msg(pid, argv[2]);
    
}
