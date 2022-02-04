/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:28:56 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/02/04 11:24:41 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_exit_client(void)
{
	ft_printf("Erreur client\n");
	exit(2);
}

/*
La fonction est appelée par send_msg() une fois le message complètement 
envoyé, elle sert à envoyer le char null (8 bits 0) au serveur pour signaler 
la fin du message.
Elle retourne 1 lorsque le char null est complètement envoyé, 0 sinon.
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
La fonction envoit 1 bit d'un char de la str qui doit être envoyée au serveur. 
A chaque appel de cette fonction, le bit suivant est envoyé et la fonction 
progresse dans l'envoi du message en conservant ses variables en static
pour qu'elles persistent entre chaque appel de fonction.
Elle retourne 1 lorsque le message est complètement envoyé, 0 sinon.
Si le message est complètement envoyé, elle appelle send_null_char_bit() qui 
prend alors le relais pour envoyer le char null marquant la fin de message au 
serveur.

128 codé en binaire sur 8 bits = 10000000
C'est ce 1 qu'on déplace en utilisant un bitwise operator pour assigner un bit 
0 ou 1 au char c
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
