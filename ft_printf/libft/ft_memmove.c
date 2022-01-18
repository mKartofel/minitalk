/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:46:10 by vfiszbin          #+#    #+#             */
/*   Updated: 2021/12/06 19:54:42 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	i = 0;
	if (pdst == NULL && psrc == NULL)
		return (NULL);
	if (psrc < pdst)
	{
		while (++i <= n)
			pdst[n - i] = psrc[n - i];
	}
	else
	{
		while (n > 0)
		{
			*(pdst++) = *(psrc++);
			n--;
		}
	}	
	return (dst);
}

/*
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*buffer;

	buffer = ft_substr(src, 0, n);
	return (ft_memcpy(dst, buffer, n));
}
*/
