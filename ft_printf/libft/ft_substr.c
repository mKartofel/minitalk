/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:38:06 by vfiszbin          #+#    #+#             */
/*   Updated: 2021/12/13 20:16:19 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_malloc(void)
{
	char	*ret_str;

	ret_str = malloc(sizeof(char));
	if (!ret_str)
		return (NULL);
	ret_str[0] = '\0';
	return (ret_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret_str;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		return (empty_malloc());
	if (start + len > len_s)
		len = len_s - start;
	ret_str = malloc(sizeof(char) * (len + 1));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret_str[i] = s[i + start];
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}
