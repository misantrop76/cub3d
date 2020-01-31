/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:59:15 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 15:59:18 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int 	draw_map(t_s *s)
{
	int x = 0;
	int y = 0;
	double i;
	double j;

	x = s->mapsize / 2;
	y = s->mapsize / 2;


	x = 0;
	y = 0;
	i = s->PosY - 10;
	j = s->PosX - 10;
	while (x < s->mapsize)
	{
		s->img.mapdata[y * s->mapsize + x] = 0xFFFFFF;
		x++;
	}
	x--;
	while (y < s->mapsize)
		s->img.mapdata[y++ * s->mapsize + x] = 0xFFFFFF;
	y--;
	while (x > 0)
		s->img.mapdata[y * s->mapsize + x--] = 0xFFFFFF;
	while (y > 0)
		s->img.mapdata[y-- * s->mapsize + x] = 0xFFFFFF;
	while (y < s->mapsize)
	{
		while (x < s->mapsize)
		{
			if (i >= 0 && j >= 0 && (int)i < s->MapY && (int)j < s->MapX && s->map[(int)i][(int)j] == 1)
				s->img.mapdata[y * s->mapsize + x] = 0xFFFFFF;
			if (i >= 0 && j >= 0 && (int)i < s->MapY && (int)j < s->MapX && s->map[(int)i][(int)j] == 2)
				s->img.mapdata[y * s->mapsize + x] = 0x6F4B04;
			j = j + (20.0 / s->mapsize);
			x++;
		}
		j = s->PosX - 10.0;
		i = i + (20.0 / s->mapsize);
		y++;
		x = 0;
	}

	i = s->PosY - 10;
	j = s->PosX - 10;
	x = s->mapsize / 2;
	y = s->mapsize / 2;
	s->img.mapdata[y * s->mapsize + x] = 0xFF0000;
	s->img.mapdata[(y - 1) * s->mapsize + (x - 1)] = 0xFF0000;
	s->img.mapdata[(y - 1) * s->mapsize + x] = 0xFF0000;
	s->img.mapdata[(y - 1) * s->mapsize + (x + 1)] = 0xFF0000;
	s->img.mapdata[y * s->mapsize + (x - 1)] = 0xFF0000;
	s->img.mapdata[y * s->mapsize + (x + 1)] = 0xFF0000;
	s->img.mapdata[(y + 1) * s->mapsize + (x - 1)] = 0xFF0000;
	s->img.mapdata[(y + 1) * s->mapsize + x] = 0xFF0000;
	s->img.mapdata[(y + 1) * s->mapsize + (x + 1)] = 0xFF0000;
	return (0);

}
