/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:08:16 by mminet            #+#    #+#             */
/*   Updated: 2020/02/18 21:18:00 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_draw_sprite(t_s *s, int id)
{
	int x;
	int y;
	int a;
	int b;

	y = -1;
	a = s->sprite[id].a;
	b = s->sprite[id].b;
	while (++y < s->sprite[id].size)
	{
		x = -1;
		while (++x < s->sprite[id].size)
		{
			if (s->sprite[id].test[x + a] == 1 && (x + a) < s->winx && (x + a)
			> 0 && (y + b) < s->winy && s->tex[5].data[(int)((double)s->tex[5].
			texy / (double)s->sprite[id].size * (double)y) * s->tex[5].texx +
			(int)((double)s->tex[5].texx / (double)s->sprite[id].size *
			(double)x)] > 0)
				s->img.data[(b + y) * s->winx + x + a] = s->tex[5].data[(int)
				((double)s->tex[5].texy / (double)s->sprite[id].size * (double)
				y) * s->tex[5].texx + (int)((double)s->tex[5].texx / (double)
				s->sprite[id].size * (double)x)];
		}
	}
	return (0);
}

int		*ft_sort(t_s *s)
{
	int a;
	int tp;
	int *sort;

	if (!(sort = malloc(sizeof(int) * s->nb_sprite)))
		return (0);
	a = -1;
	while (++a < s->nb_sprite)
		sort[a] = a;
	a = 0;
	while (a < s->nb_sprite)
	{
		if (a + 1 < s->nb_sprite && s->sprite[sort[a]].dist
		< s->sprite[sort[a + 1]].dist)
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

void	ft_sprite(t_s *s, int a)
{
	int *sort;

	while (++a < s->nb_sprite)
	{
		s->sprite[a].xx = s->sprite[a].x - s->posx;
		s->sprite[a].yy = s->sprite[a].y - s->posy;
		s->sprite[a].v = 1.0 / (s->x_plane * s->diry - s->y_plane * s->dirx);
		s->sprite[a].vx = s->sprite[a].v * (-s->diry * s->sprite[a].xx
		- -s->dirx * s->sprite[a].yy);
		s->sprite[a].vy = s->sprite[a].v * (-s->y_plane * s->sprite[a].xx
		+ s->x_plane * s->sprite[a].yy);
		s->sprite[a].dist = sqrt(pow(s->sprite[a].xx, 2.0)
		+ pow(s->sprite[a].yy, 2.0));
		s->sprite[a].size = (int)(s->winy / s->sprite[a].dist);
		s->sprite[a].a = (int)(s->winx / 2 * (1 + s->sprite[a].vx / s->sprite
		[a].vy)) - (s->sprite[a].size / 2);
		s->sprite[a].b = (s->winy / 2) - (s->sprite[a].size / 2);
	}
	sort = ft_sort(&*s);
	a = -1;
	while (++a < s->nb_sprite)
		if (s->sprite[sort[a]].spritex)
			ft_draw_sprite(&*s, sort[a]);
	free(sort);
}
