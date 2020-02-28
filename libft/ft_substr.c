/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:59:04 by mminet            #+#    #+#             */
/*   Updated: 2020/02/28 16:07:02 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	int				i;
	unsigned int	a;

	a = 0;
	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		dest = ft_calloc(1, 1);
		return (dest);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	if (!(dest = malloc(sizeof(char) * len + 1)))
		return (0);
	while (len > 0)
	{
		dest[i] = s[i + start];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}
