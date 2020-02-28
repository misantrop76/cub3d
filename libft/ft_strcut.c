/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:50:00 by mminet            #+#    #+#             */
/*   Updated: 2020/02/28 16:44:42 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strcut(char *str, char *set)
{
	int		i;
	int		j;
	int		len;
	char	*s;

	i = 0;
	len = 0;
	while (str[i])
		if (!(ft_strchr(set, str[i++])))
			len++;
	if (!(s = malloc(sizeof(char) * (len + 1))))
		return (0);
	s[len] = '\0';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!(strchr(set, str[i])))
			s[j++] = str[i];
		i++;
	}
	return (s);
}
