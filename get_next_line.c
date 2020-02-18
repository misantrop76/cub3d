/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:41:00 by mminet            #+#    #+#             */
/*   Updated: 2020/02/18 21:07:19 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdel(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

char	*ft_get_line(int fd, int *ret, char *rest)
{
	char buffer[101];
	char *rest2;

	*ret = read(fd, buffer, 100);
	buffer[*ret] = '\0';
	rest2 = rest;
	rest = ft_strjoin(rest, buffer);
	ft_strdel(rest2);
	return (rest);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest = NULL;
	char		*line2;
	char		*str;
	int			ret;

	ret = 1;
	if (!line || fd < 0 || (rest == NULL && (!(rest = ft_strdup("")))))
		return (-1);
	while (ret)
	{
		if ((str = ft_strchr(rest, '\n')) && str != 0)
		{
			*str = '\0';
			*line = ft_strdup(rest);
			line2 = rest;
			rest = ft_strdup(str + 1);
			ft_strdel(line2);
			return (1);
		}
		rest = ft_get_line(fd, &ret, rest);
	}
	*line = ft_strdup(rest);
	return (0);
}
