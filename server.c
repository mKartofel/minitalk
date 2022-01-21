/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:29:28 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/01/21 19:42:25 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include <signal.h>

#define NB_BITS_INT sizeof(int)
#define NB_BITS_CHAR sizeof(char)

typedef struct s_recvd_char
{
	int char_bits[8];
	int nb_recvd;
	int msg_len_bits[32];
	int msg_len;
	char *message;
	int i;
} t_recvd_char;

t_recvd_char g_recvd_char = {.char_bits={0}, .nb_recvd=0, .msg_len_bits={0}, .msg_len=0, .i=0};

void add_char()
{
	char c;
	
	// ft_printf("recvd= ");
	// for(int i=0; i < 8; i++)
	// 	ft_printf("%d",g_recvd_char.char_bits[i]);
	// ft_printf("\n");
	
	c =	g_recvd_char.char_bits[0] << 7 |
		g_recvd_char.char_bits[1]  << 6 |
		g_recvd_char.char_bits[2]  << 5 |
		g_recvd_char.char_bits[3]  << 4 |
		g_recvd_char.char_bits[4]  << 3 |
		g_recvd_char.char_bits[5]  << 2 |
		g_recvd_char.char_bits[6]  << 1 |
		g_recvd_char.char_bits[7]  << 0;
	
	g_recvd_char.message[g_recvd_char.i] = c;
	g_recvd_char.i++;
	
	if (g_recvd_char.i >= g_recvd_char.msg_len)
	{
		g_recvd_char.message[g_recvd_char.i] = '\0';
		ft_printf("%s", g_recvd_char.message);
		free(g_recvd_char.message);
		g_recvd_char.i = 0;
		g_recvd_char.msg_len = 0;
	}
}

void add_int()
{
	// for(int i=0; i < 32; i++)
	// 	ft_printf("%d", g_recvd_char.msg_len_bits[i]);
	// ft_printf("\n");
		
	g_recvd_char.msg_len =	g_recvd_char.msg_len_bits[0] << 31 |
							g_recvd_char.msg_len_bits[1]  << 30 |
							g_recvd_char.msg_len_bits[2]  << 29 |
							g_recvd_char.msg_len_bits[3]  << 28 |
							g_recvd_char.msg_len_bits[4]  << 27 |
							g_recvd_char.msg_len_bits[5]  << 26 |
							g_recvd_char.msg_len_bits[6]  << 25 |
							g_recvd_char.msg_len_bits[7]  << 24 |
							g_recvd_char.msg_len_bits[8]  << 23 |
							g_recvd_char.msg_len_bits[9]  << 22 |
							g_recvd_char.msg_len_bits[10]  << 21 |
							g_recvd_char.msg_len_bits[11]  << 20 |
							g_recvd_char.msg_len_bits[12]  << 19 |
							g_recvd_char.msg_len_bits[13]  << 18 |
							g_recvd_char.msg_len_bits[14]  << 17 |
							g_recvd_char.msg_len_bits[15]  << 16 |
							g_recvd_char.msg_len_bits[16]  << 15 |
							g_recvd_char.msg_len_bits[17]  << 14 |
							g_recvd_char.msg_len_bits[18]  << 13 |
							g_recvd_char.msg_len_bits[19]  << 12 |
							g_recvd_char.msg_len_bits[20]  << 11 |
							g_recvd_char.msg_len_bits[21]  << 10 |
							g_recvd_char.msg_len_bits[22]  << 9 |
							g_recvd_char.msg_len_bits[23]  << 8 |
							g_recvd_char.msg_len_bits[24]  << 7 |
							g_recvd_char.msg_len_bits[25]  << 6 |
							g_recvd_char.msg_len_bits[26]  << 5 |
							g_recvd_char.msg_len_bits[27]  << 4 |
							g_recvd_char.msg_len_bits[28]  << 3 |
							g_recvd_char.msg_len_bits[29]  << 2 |
							g_recvd_char.msg_len_bits[30]  << 1 |
							g_recvd_char.msg_len_bits[31]  << 0;
							
	g_recvd_char.message = malloc(sizeof(char) * g_recvd_char.msg_len + 1);
	if (!g_recvd_char.message)
		exit(1);
	// ft_printf("msg_len = %d\n", g_recvd_char.msg_len);
}

void handle_SIGUSR1(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	int i;
	
	
	if (g_recvd_char.msg_len == 0)
	{
		i = g_recvd_char.nb_recvd;
		g_recvd_char.msg_len_bits[i] = 0;
		g_recvd_char.nb_recvd++;
		if (g_recvd_char.nb_recvd >= 32)
		{
			add_int();
			g_recvd_char.nb_recvd = 0;
		}
	}
	else
	{
		i = g_recvd_char.nb_recvd;
		g_recvd_char.char_bits[i] = 0;
		g_recvd_char.nb_recvd++;
		if (g_recvd_char.nb_recvd >= 8)
		{
			add_char();
			g_recvd_char.nb_recvd = 0;
		}		
	}

	kill(info->si_pid, SIGUSR1);

}

void handle_SIGUSR2(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	int i;
	
	
	if (g_recvd_char.msg_len == 0)
	{
		i = g_recvd_char.nb_recvd;
		g_recvd_char.msg_len_bits[i] = 1;
		g_recvd_char.nb_recvd++;
		if (g_recvd_char.nb_recvd >= 32)
		{
			add_int();
			g_recvd_char.nb_recvd = 0;
		}
	}
	else
	{
		i = g_recvd_char.nb_recvd;
		g_recvd_char.char_bits[i] = 1;
		g_recvd_char.nb_recvd++;
		if (g_recvd_char.nb_recvd >= 8)
		{
			add_char();
			g_recvd_char.nb_recvd = 0;
		}		
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

	while (1){
		pause();
		//ft_printf("pause ret : %d\n", ret);
	}
	
	return 0;
}
