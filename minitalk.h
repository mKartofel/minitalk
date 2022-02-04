/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:09:31 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/02/04 11:21:58 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "ft_printf/includes/ft_printf.h"
# include <stdlib.h>

void	send_signal(char *s_msg, int i, int s_pid, int nb_bits_sent);
void	handle_exit_client(void);

#endif