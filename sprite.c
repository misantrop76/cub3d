/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sprite.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:06:37 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 17:12:35 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_draw_sprite(t_s *s, int id)
{
	int x = 0;
	int y = 0;
	int a = s->sprite[id].a;
	int b = s->sprite[id].b;

	while (y < s->sprite[id].size)
	{
		while (x < s->sprite[id].size)
		{
			if (s->sprite[id].test[x + a] == 1 && (x + a) < s->WinX && (x + a) > 0 && (y + b) < s->WinY && s->tex[5].data[(int)((double)s->tex[5].texY / (double)s->sprite[id].size * (double)y) * s->tex[5].texX + (int)((double)s->tex[5].texX / (double)s->sprite[id].size * (double)x)] > 0)
				s->img.data[(b + y) * s->WinX + x + a] = s->tex[5].data[(int)((double)s->tex[5].texY / (double)s->sprite[id].size * (double)y) * s->tex[5].texX + (int)((double)s->tex[5].texX / (double)s->sprite[id].size * (double)x)];
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int 	*ft_sort(t_s *s)
{
	int a;
	int tp;
	int *sort;

	if (!(sort = malloc(sizeof(int) * s->nb_sprite)))
		return (0);
	a = 0;
	while (a < s->nb_sprite)
	{
		sort[a] = a;
		a++;
	}
	a = 0;
	while (a < s->nb_sprite)
	{
		if (a + 1 < s->nb_sprite && s->sprite[sort[a]].dist < s->sprite[sort[a + 1]].dist)
		{
			tp = sort[a];
			sort[a] = sort[a + 1];
			sort[a + 1] = tp;
			a = 0;
		}
		else
			a++;
	}
	return (sort);
}

void	ft_sprite(t_s *s)
{
	int a = 0;
	int *sort;

	while (a < s->nb_sprite)
	{
		s->sprite[a].X = s->sprite[a].x - s->PosX;
		s->sprite[a].Y = s->sprite[a].y - s->PosY;
		s->sprite[a].v = 1.0 / (s->x_plane * s->dirY - s->y_plane * s->dirX);
		s->sprite[a].vx = s->sprite[a].v * (-s->dirY * s->sprite[a].X - -s->dirX * s->sprite[a].Y);
		s->sprite[a].vy = s->sprite[a].v * (-s->y_plane * s->sprite[a].X  + s->x_plane * s->sprite[a].Y);
		s->sprite[a].dist = sqrt(pow(s->sprite[a].X, 2.0) + pow(s->sprite[a].Y,2.0));
		s->sprite[a].a = (int)(s->WinX / 2 * (1 + s->sprite[a].vx / s->sprite[a].vy)) - (s->WinX / 3 / s->sprite[a].dist);
		s->sprite[a].size = (int)(s->WinY / s->sprite[a].dist);
		s->sprite[a].b = (s->WinY / 2) - (s->sprite[a].size / 2);
		a++;
	}
	sort = ft_sort(&*s);
	a = 0;
	while (a < s->nb_sprite)
	{
		if (s->sprite[sort[a]].spritex)
			ft_draw_sprite(&*s, sort[a]);
		a++;
	}
}
