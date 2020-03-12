/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:50:00 by mminet            #+#    #+#             */
/*   Updated: 2020/03/05 18:25:18 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!(s = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (0);
	s[ft_strlen(str)] = '\0';
	while (str[i])
	{
		if (str[i] == ' ')
			s[i] = '1';
		else
			s[i] = str[i];
		i++;
	}
	return (s);
}
