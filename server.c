/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:29:28 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/01/20 20:07:54 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include <signal.h>

typedef struct s_recvd_char
{
	int char_bits[8];
	int nb_recvd;
} t_recvd_char;

t_recvd_char g_recvd_char = { .char_bits={0}, .nb_recvd=0 };

void print_char()
{
	ft_printf("In print_char\n\n\n");
	char c;

	for(int i=0; i < 8; i++)
		ft_printf("%d",g_recvd_char.char_bits[i]);
	ft_printf("\n");
	
	
	c =	g_recvd_char.char_bits[0] << 7 |
		g_recvd_char.char_bits[1]  << 6 |
		g_recvd_char.char_bits[2]  << 5 |
		g_recvd_char.char_bits[3]  << 4 |
		g_recvd_char.char_bits[4]  << 3 |
		g_recvd_char.char_bits[5]  << 2 |
		g_recvd_char.char_bits[6]  << 1 |
		g_recvd_char.char_bits[7]  << 0;
		
	ft_printf("%c",c);
}

void handle_SIGUSR1(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	ft_printf("nb_recvd = %d\n", g_recvd_char.nb_recvd);
	if (g_recvd_char.nb_recvd == 7)
	{
		print_char();
		g_recvd_char.nb_recvd = 0;
	}
	else
	{
		int i = g_recvd_char.nb_recvd;
		g_recvd_char.char_bits[i] = 0; //sert à rien
		g_recvd_char.nb_recvd++;
	}

	kill(info->si_pid, SIGUSR1);

}

void handle_SIGUSR2(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	ft_printf("nb_recvd = %d\n", g_recvd_char.nb_recvd);
	if (g_recvd_char.nb_recvd == 7)
	{
		print_char();
		g_recvd_char.nb_recvd = 0;
	}
	else
	{
		int i = g_recvd_char.nb_recvd;
		g_recvd_char.char_bits[i] = 1;
		g_recvd_char.nb_recvd++;
	}

	kill(info->si_pid, SIGUSR1);

}

int main (void)
{
	struct sigaction action_SIGUSR1, action_SIGUSR2;

	ft_printf("%d\n", getpid());

	action_SIGUSR1.sa_sigaction = handle_SIGUSR1;
	sigemptyset (&action_SIGUSR1.sa_mask);
	action_SIGUSR1.sa_flags = SA_SIGINFO;

	action_SIGUSR2.sa_sigaction = handle_SIGUSR2;
	sigemptyset (&action_SIGUSR2.sa_mask);
	action_SIGUSR2.sa_flags = SA_SIGINFO;

	sigaction (SIGUSR1, &action_SIGUSR1, NULL);
	sigaction (SIGUSR2, &action_SIGUSR2, NULL);

	ft_bzero(g_recvd_char.char_bits, 8);

	while (1){
		pause();
		//ft_printf("pause ret : %d\n", ret);
	}
	
	return 0;
}
