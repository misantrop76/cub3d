/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:08:00 by mminet            #+#    #+#             */
/*   Updated: 2020/03/04 20:01:58 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting3(t_s *s, int a, int x)
{
	int i;

	i = -1;
	x = 0;
	a = 0;
	ft_sprite(&*s, i);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.img_ptr, 0, 0);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.map_ptr, 0, 0);
	a = -1;
	x = -1;
	while (++a < s->nb_sprite)
	{
		x = -1;
		while (++x < s->winx)
			s->sprite[a].test[x] = 0;
	}
}

void	ray_casting2(t_s *s, int x)
{
	if (s->turn_right == 1)
		s->mvback += 50;
	if (s->turn_left == 1)
		s->mvback -= 50;
	if (s->mvback + x > 3000)
		s->mvback = 0;
	if (s->mvback + x < 0)
		s->mvback = 3000 - x;
	while (x < s->winx)
	{
		ray_casting_init(&*s, x);
		s->lineheight = (int)(s->winy / s->walldist);
		s->start = -s->lineheight / 2 + s->winy / 2;
		if (s->start < 0)
			s->start = 0;
		s->end = s->lineheight / 2 + s->winy / 2;
		if (s->end >= s->winy)
			s->end = s->winy - 1;
		if (s->side == 1)
			s->color = 0x2D27E1;
		else
			s->color = 0x546AF7;
		draw_wall(x, s->start - 1, s->end, &*s);
		x++;
	}
}
