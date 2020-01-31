/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:00:57 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 23:04:00 by mminet      ###    #+. /#+    ###.fr     */
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
	s->x_text = (int)(s->x_wall * (double)s->tex[id].texX);
	if (s->side == 0 && s->x_raydir > 0)
		s->x_text = s->tex[id].texX - s->x_text - 1;
	if (s->side == 1 && s->y_raydir < 0)
		s->x_text = s->tex[id].texX - s->x_text - 1;
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
		if (x < s->WinX && start < s->WinY)
		{
			s->y_text = abs((((start * 256 - s->WinY * 128 +
			s->lineheight * 128) * 64) / s->lineheight) / 256);
			s->img.data[start * s->WinX + x] = s->tex[id].data[(s->y_text %
			64 * s->tex[id].size_l + s->x_text % 64 * s->tex[id].bpp / 8) / 4];
			start++;
		}
	}
	while (end < s->WinY - 1)
	{
		s->img.data[end * s->WinX + x] = s->floor_color;
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
	texpos = (start - s->WinY / 2 + s->lineheight / 2) * step;
	i = 0;
	j = 0;
	while (i < start)
	{
		if (s->tex[0].path[0] != '\0')
			s->img.data[i * s->WinX + x] =
			s->tex[0].data[j * s->tex[0].texX + x + s->mvback];
		else
			s->img.data[i * s->WinX + x] = s->sky_color;
		i++;
		j++;
		if (j >= s->tex[0].texX)
			j = 0;
	}
	start += 2;
	draw_wall2(&*s, start, end, x);
}
