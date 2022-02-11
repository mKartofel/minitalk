/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:28:56 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/02/11 15:19:11 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_exit_client(void)
{
	ft_printf("Erreur client\n");
	exit(2);
}

/*
The function is called by send_msg() once the message is completely sent,
it sends the null char (eight 0 bits) to notify the server that the
message is over.
The function returns 1 when the null char is completely sent, 0 otherwise.
*/
int	send_null_char_bit(int pid)
{
	static int	s_pid = 0;
	static int	nb_null_bits_sent = 0;

	if (pid != 0)
		s_pid = pid;
	if (kill(s_pid, SIGUSR1) == -1)
		handle_exit_client();
	nb_null_bits_sent++;
	if (nb_null_bits_sent >= 8)
		return (1);
	return (0);
}

/*
The function sends 1 bit of a char from the string that needs to be sent to the 
server. Each time the function is called, the next bit is sent and the function
keeps track of it progress through the string with static variables that
persist between each function call.
The function returns 1 when the message is completely sent, 0 otherwise.
If the message is completely sent, it calls send_null_char_bit() which
in turns send a null char to notify the server that the message is
over.

128 in binary, coded on 8 bits = 10000000
It is this 1 that is moved using bitwise operators to put each bit to
0 or 1 in the char we're sending.
*/
int	send_char_bit(int pid, char *msg)
{
	static char	*s_msg = NULL;
	static int	nb_bits_sent = 0;
	static int	i = 0;
	static int	s_pid = 0;

	if (msg != NULL)
		s_msg = msg;
	if (pid != 0)
		s_pid = pid;
	if (s_msg[i] == '\0')
	{
		send_null_char_bit(s_pid);
		return (1);
	}
	send_signal(s_msg, i, s_pid, nb_bits_sent);
	nb_bits_sent++;
	if (nb_bits_sent >= 8)
	{
		nb_bits_sent = 0;
		i++;
	}
	return (0);
}

void	handle_sigusr(int signum)
{
	static int	msg_sent = 0;
	static int	end_of_msg_sent = 0;

	if (end_of_msg_sent)
	{
		ft_printf("Message envoyé au serveur\n");
		exit(0);
	}
	if (signum == SIGUSR1)
	{
		if (msg_sent == 0)
			msg_sent = send_char_bit(0, NULL);
		else
			end_of_msg_sent = send_null_char_bit(0);
	}
	else if (signum == SIGUSR2)
	{
		ft_printf("Le serveur s'est interrompu, arrêt du client...\n");
		handle_exit_client();
	}
}

int	main(int argc, char **argv)
{
	int	pid;

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
	signal (SIGUSR1, handle_sigusr);
	signal (SIGUSR2, handle_sigusr);
	send_char_bit(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
