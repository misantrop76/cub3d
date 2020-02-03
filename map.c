/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:59:15 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/02 16:22:51 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

	size = s->mapsize / 30;
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
	y = 0;
	while (y < s->mapsize)
	{
		x = 0;
		j = s->posx - 10.0;
		while (x < s->mapsize)
		{
			if (i >= 0 && j >= 0 && (int)i < s->mapy &&
			(int)j < s->mapx && s->map[(int)i][(int)j] != 0)
				s->img.mapdata[y * s->mapsize + x] =
				16777215 / s->map[(int)i][(int)j];
			j = j + (20.0 / s->mapsize);
			x++;
		}
		i = i + (20.0 / s->mapsize);
		y++;
	}
	middle_point(&*s);
}
