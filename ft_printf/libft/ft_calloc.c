/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:32:29 by vfiszbin          #+#    #+#             */
/*   Updated: 2021/12/05 19:44:13 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	int		len;

	p = NULL;
	len = size * nmemb;
	p = malloc(len);
	if (!p)
		return (NULL);
	ft_memset(p, 0, len);
	return (p);
}
