/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:00:57 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/02 16:25:16 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		draw_wall_init(t_s *s)
{
	int		id;

	if (s->side == 0 && s->x_raydir < 0)
		id = 1;
	else if (s->side == 0)
		id = 3;
	if (s->side == 1 && s->y_raydir > 0)
		id = 2;
	else if (s->side == 1)
		id = 4;
	if (s->side == 0)
		s->x_wall = s->y_raypos + s->walldist * s->y_raydir;
	else
		s->x_wall = s->x_raypos + s->walldist * s->x_raydir;
	s->x_text = (int)(s->x_wall * (double)s->tex[id].texx);
	if (s->side == 0 && s->x_raydir > 0)
		s->x_text = s->tex[id].texx - s->x_text - 1;
	if (s->side == 1 && s->y_raydir < 0)
		s->x_text = s->tex[id].texx - s->x_text - 1;
	s->x_text = abs(s->x_text);
	s->i = id;
	return (id);
}

void	draw_wall2(t_s *s, int start, int end, int x)
{
	int id;

	id = s->i;
	while (start < end)
	{
		if (x < s->winx && start < s->winy)
		{
			s->y_text = abs((((start * 256 - s->winy * 128 +
			s->lineheight * 128) * 64) / s->lineheight) / 256);
			s->img.data[start * s->winx + x] = s->tex[id].data[(s->y_text %
			64 * s->tex[id].size_l + s->x_text % 64 * s->tex[id].bpp / 8) / 4];
			start++;
		}
	}
	while (end < s->winy - 1)
	{
		s->img.data[end * s->winx + x] = s->floor_color;
		end++;
	}
}

void	draw_wall(int x, int start, int end, t_s *s)
{
	int		i;
	int		j;
	double	step;
	double	texpos;
	int		id;

	step = 0;
	id = draw_wall_init(&*s);
	texpos = (start - s->winy / 2 + s->lineheight / 2) * step;
	i = 0;
	j = 0;
	while (i < start)
	{
		if (s->tex[0].path[0] != '\0')
			s->img.data[i * s->winx + x] =
			s->tex[0].data[j * s->tex[0].texx + x + s->mvback];
		else
			s->img.data[i * s->winx + x] = s->sky_color;
		i++;
		j++;
		if (j >= s->tex[0].texx)
			j = 0;
	}
	start += 2;
	draw_wall2(&*s, start, end, x);
}
