/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:07:09 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/02/04 11:25:11 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(char *s_msg, int i, int s_pid, int nb_bits_sent)
{
	if ((s_msg[i] & (128 >> nb_bits_sent)) != 0)
	{
		if (kill(s_pid, SIGUSR2) == -1)
			handle_exit_client();
	}
	else
	{
		if (kill(s_pid, SIGUSR1) == -1)
			handle_exit_client();
	}
}
