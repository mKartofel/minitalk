/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:24:55 by vfiszbin          #+#    #+#             */
/*   Updated: 2021/12/18 14:31:02 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_uint_fd(unsigned int n, int fd, int *nb_char)
{
	if (n >= 10)
		ft_printnbr_fd(n / 10, fd, nb_char);
	ft_printchar_fd((n % 10) + '0', fd, nb_char);
}
