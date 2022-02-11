/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:06:48 by vfiszbin          #+#    #+#             */
/*   Updated: 2021/12/06 13:02:41 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ret_str;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	ret_str = malloc(sizeof(char) * (i + 1));
	if (!ret_str)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[++j])
	{
		ret_str[i] = s1[j];
		i++;
	}
	j = -1;
	while (s2[++j])
	{
		ret_str[i] = s2[j];
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}
