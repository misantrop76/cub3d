/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:06:00 by mminet            #+#    #+#             */
/*   Updated: 2020/03/06 16:05:10 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_param(t_s *s)
{
	int i;

	i = 0;
	if (s->str)
	{
		while (s->str[i])
			ft_free(s->str[i++]);
		free(s->str);
	}
	i = 0;
	if (s->map)
	{
		while (s->map[i])
			ft_free(s->map[i++]);
		free(s->map);
	}
	i = 0;
	if (s->sprite)
		while (i < s->nb_sprite)
			free(s->sprite[i++].test);
	if (s->sprite)
		free(s->sprite);
}

void	ft_exit2(t_s *s, char *str)
{
	if (ft_strncmp(str, "save", 5) == 0)
	{
		mlx_destroy_image(s->mlx_ptr, s->img.img_ptr);
		mlx_destroy_image(s->mlx_ptr, s->img.map_ptr);
	}
	if (s->win_ptr)
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	ft_free_param(s);
	exit(0);
}

int		ft_exit(char *str, t_s *s)
{
	int len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "usage", 6) == 0)
	{
		ft_putstr_fd("ERROR\nUSAGE:\n\n		./Cub3d file.cub\n", 1);
		ft_putstr_fd("flags : --save\n\n\n", 1);
	}
	else if (ft_strncmp(str, "param", 6) == 0)
		ft_putstr_fd("\nERROR\nWITH SETTINGS\n\n", 1);
	else if (ft_strncmp(str, "path", 5) == 0)
	{
		ft_putstr_fd("\nERROR\nFAIL TO LOAD TEXTURE\n\n", 1);
		ft_putstr_fd("CHECK THE PATH TEXTURE\n\n", 1);
	}
	else if (ft_strncmp(str, "map", 4) == 0)
	{
		ft_putstr_fd("\nERROR\nWITH MAP 		EXAMPLE:\n\n", 1);
		ft_putstr_fd("1 1 1 1 1\n1 0 0 0 1\n1 2 0 2 1", 1);
		ft_putstr_fd("\n1 0 0 N 1\n1 1 1 1 1\n\n", 1);
	}
	else if (ft_strncmp(str, "save", 5) != 0)
		ft_putstr_fd(str, 1);
	ft_exit2(s, str);
	return (0);
}

int		ft_error(t_s *s)
{
	ft_exit("", s);
	return (0);
}

int		jump_space(char *str, int j, int t, t_s *s)
{
	while (!(ft_isdigit(str[j])))
		j++;
	while (ft_isdigit(str[j]))
		j++;
	if (t)
		while (str[j])
			if (str[j++] != ' ')
				ft_exit("param", s);
	return (j);
}
