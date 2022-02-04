/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 11:22:14 by vfiszbin          #+#    #+#             */
/*   Updated: 2021/12/18 14:52:09 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printnbr_fd(int n, int fd, int *nb_char)
{
	if (n == -2147483648)
	{
		ft_printstr_fd("-2147483648", fd, nb_char);
		return ;
	}
	if (n < 0)
	{
		n *= (-1);
		ft_printchar_fd('-', fd, nb_char);
	}
	if (n >= 10)
		ft_printnbr_fd(n / 10, fd, nb_char);
	ft_printchar_fd((n % 10) + '0', fd, nb_char);
}
