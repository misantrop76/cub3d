/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:00:57 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 17:02:09 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(int x, int start, int end, t_s *s)
{
	int i = 0;
	int j = 0;
	double step;
	double texpos;
	int id;

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
	texpos = (start - s->WinY / 2 + s->lineheight / 2) * step;
	while (i < start)
	{
		s->img.data[i * s->WinX + x] = s->tex[0].data[j * s->tex[0].texX + x + s->mvback];
		i++;
		j++;
		if (j  >= s->tex[0].texX)
			j = 0;
	}
	start += 2;
	while (start < end)
	{
		if (x < s->WinX && start < s->WinY)
		{
			s->y_text = abs((((start * 256 - s->WinY * 128 + s->lineheight * 128) * 64) / s->lineheight) / 256);
			s->img.data[start * s->WinX + x] = s->tex[id].data[(s->y_text % 64 * s->tex[id].size_l + s->x_text % 64 * s->tex[id].bpp /8) / 4];
			//s->img.data[start * s->WinX + x] = s->color;
			start++;
		}
	}
	while (end < s->WinY)
	{
		s->img.data[end * s->WinX + x] = 0x2A2B35;
		end++;
	}
}
