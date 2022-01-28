/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:29:28 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/01/28 21:35:19 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/includes/ft_printf.h"
#include <signal.h>

#include<stdio.h>

void handle_exit(int pid, char* message)
{
	printf("IN HANDLE EXIT\n");
	if(message)
		free(message);
	(void)pid;
	//kill(pid, SIGUSR2);
	exit(1);
}

/*
Ajoute le char reçu au message en concaténant les deux. Retourne la chaîne concaténée et libère le message passé en argument.
Si le message était NULL, la chaîne retournée est uniquement composée du char reçu.
*/
char* add_char_to_msg(char *message, char c, int pid)
{
	char* ret_str;
	char c_str[2];

	if (message == NULL)
	{
		ret_str = malloc(sizeof(char)*2);
		if (!ret_str)
		{
			printf("fail malloc ret_str\n");
			handle_exit(pid, message);
		}
		ret_str[0] = c;
		ret_str[1] = '\0';
		return ret_str;
	}
	c_str[0] = c;
	c_str[1] = '\0';
	ret_str = ft_strjoin(message, c_str);
	if (!ret_str)
	{
		printf("ret_str empty\n");
		handle_exit(pid, message);

	}
	return ret_str;
}

char * print_message(char* message)
{
	ft_putstr_fd(message,1);
	free(message);
	return NULL;
}

/*
128 codé en binaire sur 8 bits = 10000000
C'est ce 1 qu'on déplace en utilisant un bitwise operator pour assigner un bit 0 ou 1 au char c

c == 0 signifie qu'on a reçu le char nul qui marque la fin du message

Il est très important de garder s_pid en static car info->si_pid peut devenir 0 dans certains cas, ce qui fait que le
serveur s'envoie des SIGUSR1 à lui même en boucle !
*/
void handle_SIGUSR(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char c;
	static int nb_bits_rcvd = 0;
	static char *message = NULL;
	static int s_pid = 0;
	
	(void)ucontext;

	if (info->si_pid != 0)
		s_pid = info->si_pid ;

	if (signum == SIGUSR1)
	{
		//printf("0\n");
		c = c & ~(128 >> nb_bits_rcvd);
	}
		
	else if (signum == SIGUSR2)
	{
		//printf("1\n");
		c = c | (128 >> nb_bits_rcvd);
	}

	nb_bits_rcvd++;

	if (nb_bits_rcvd == 8)
	{
		if (c != 0)
			message = add_char_to_msg(message, c, s_pid);
		else
			message = print_message(message);
		nb_bits_rcvd = 0;
		c = 128;
	}
	//printf("si_pid=%d\n",info->si_pid);
	if (kill(s_pid, SIGUSR1) == -1)
	{
		printf("kill failed\n");
		handle_exit(s_pid, message);

	}

}


int main (void)
{
	struct sigaction action_SIGUSR;

	action_SIGUSR.sa_sigaction = handle_SIGUSR;
	sigemptyset (&action_SIGUSR.sa_mask);
	action_SIGUSR.sa_flags = SA_SIGINFO;

	sigaction (SIGUSR1, &action_SIGUSR, NULL);
	sigaction (SIGUSR2, &action_SIGUSR, NULL);

	// signal(SIGINT, handler_exit);
	// signal(SIGTERM, handler_exit);

	ft_printf("%d\n", getpid());

	while (1)
		pause();
	
	return 0;
}
