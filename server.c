/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:29:28 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/02/11 13:37:05 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_exit(int pid, char *message)
{
	if (message)
		free(message);
	(void)pid;
	exit(1);
}

/*
Add the received char to the message by concatenating the two. Returns
the concatenated string and free the message passed in argument.
If message is NULL, the returned string only contains the received char.
*/
char	*add_char_to_msg(char *message, char c, int pid)
{
	char	*ret_str;
	char	c_str[2];

	if (message == NULL)
	{
		ret_str = malloc(sizeof(char) * 2);
		if (!ret_str)
			handle_exit(pid, message);
		ret_str[0] = c;
		ret_str[1] = '\0';
		return (ret_str);
	}
	c_str[0] = c;
	c_str[1] = '\0';
	ret_str = ft_strjoin(message, c_str);
	if (!ret_str)
		handle_exit(pid, message);
	free(message);
	return (ret_str);
}

char	*print_message(char *message)
{
	ft_putstr_fd(message, 1);
	free(message);
	return (NULL);
}

/*
128 in binary, coded on 8 bits = 10000000
It is this 1 that is moved using bitwise operators to put each bit to
0 or 1 in the char.
c == 0 means that we received the null char, so the message is over.

It is very important to keep a static s_pid because nfo->si_pid can become 0
in some cases, causing the server to send itself SIGUSR1 indefinitely !
*/
void	handle_sigusr(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char	c;
	static int				nb_bits_rcvd = 0;
	static char				*message = NULL;
	static int				s_pid = 0;

	(void)ucontext;
	if (info->si_pid != 0)
		s_pid = info->si_pid ;
	if (signum == SIGUSR1)
		c = c & ~(128 >> nb_bits_rcvd);
	else if (signum == SIGUSR2)
		c = c | (128 >> nb_bits_rcvd);
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
	if (kill(s_pid, SIGUSR1) == -1)
		handle_exit(s_pid, message);
}

/*
To block other signals during the handler's execution, we have to specify
the sa_mask member of the sigaction struct.
It prevents the handler form being interrupted by another signal.

We add SIGINT and SIGQUIT to the signal set so they are blocked
if the handler is executing.

The SA_SIGINFO flag is added in the sa_flags member of the sigaction struct
to obtain additionnal information on the signal, such as the PID of the
process who sent the signal.

https://www.gnu.org/software/libc/manual/html_node/Blocking-for-Handler.html
*/
int	main(void)
{
	struct sigaction	s_action_sigusr;
	sigset_t			block_mask;

	sigemptyset (&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	s_action_sigusr.sa_handler = 0;
	s_action_sigusr.sa_sigaction = handle_sigusr;
	s_action_sigusr.sa_mask = block_mask;
	s_action_sigusr.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &s_action_sigusr, NULL);
	sigaction (SIGUSR2, &s_action_sigusr, NULL);
	ft_printf("%d\n", getpid());
	while (1)
		pause();
	return (0);
}
