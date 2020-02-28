/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:41:17 by mminet            #+#    #+#             */
/*   Updated: 2020/02/28 16:06:51 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && n > 0)
	{
		n = n + j;
		j = 0;
		while (str[i + j] == to_find[j] && n > 0)
		{
			j++;
			n--;
			if (to_find[j] == '\0')
				return ((char *)str + i);
		}
		i++;
		n--;
	}
	return (0);
}
