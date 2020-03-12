/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:41:12 by mminet            #+#    #+#             */
/*   Updated: 2020/03/06 15:48:24 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	edge(t_s *s)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < s->mapsize)
	{
		s->img.mapdata[0 * s->mapsize + x] = 0xFFFFFF;
		s->img.mapdata[(s->mapsize - 1) * s->mapsize + x] = 0xFFFFFF;
		x++;
	}
	while (y < s->mapsize)
	{
		s->img.mapdata[y * s->mapsize + 0] = 0xFFFFFF;
		s->img.mapdata[y * s->mapsize + (s->mapsize - 1)] = 0xFFFFFF;
		y++;
	}
}

void	middle_point(t_s *s)
{
	int x;
	int y;
	int size;

	size = s->mapsize / 50;
	x = (s->mapsize / 2) - (size / 2);
	y = (s->mapsize / 2) - (size / 2);
	while (y < ((s->mapsize / 2) - (size / 2)) + size)
	{
		while (x < ((s->mapsize / 2) - (size / 2)) + size)
		{
			s->img.mapdata[y * s->mapsize + x] = 0xFF0000;
			x++;
		}
		x = (s->mapsize / 2) - (size / 2);
		y++;
	}
	edge(&*s);
}

void	draw_map(t_s *s)
{
	int		x;
	int		y;
	double	i;
	double	j;

	i = s->posy - 10;
	y = -1;
	while (++y < s->mapsize)
	{
		x = 0;
		j = s->posx - 10.0;
		while (x < s->mapsize)
		{
			if (i >= 0 && j >= 0 && (int)i < s->mapy && j <
			ft_strlen(s->map[(int)i]) && s->map[(int)i][(int)j] != '0')
				s->img.mapdata[y * s->mapsize + x] =
				0x0073CE / (s->map[(int)i][(int)j] - 48);
			else
				s->img.mapdata[y * s->mapsize + x] = 0;
			j = j + (20.0 / s->mapsize);
			x++;
		}
		i = i + (20.0 / s->mapsize);
	}
	middle_point(&*s);
}
