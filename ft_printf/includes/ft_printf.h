/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:38:13 by vfiszbin          #+#    #+#             */
/*   Updated: 2021/12/18 14:45:38 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"
# define HEXA "0123456789abcdef"
# define HEXAMAJ "0123456789ABCDEF"

int		ft_printf(const char *fmt, ...);
void	ft_printstr_fd(char *s, int fd, int *nb_char);
void	ft_printchar_fd(char c, int fd, int *nb_char);
void	ft_printnbr_fd(int n, int fd, int *nb_char);
void	ft_printnbr_base(unsigned int nbr, char *base, int *nb_char);
void	ft_printptr_base(unsigned long long nbr, char *base, int *nb_char);
void	ft_print_uint_fd(unsigned int n, int fd, int *nb_char);

#endif