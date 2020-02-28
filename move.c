/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:41:26 by mminet            #+#    #+#             */
/*   Updated: 2020/02/25 20:18:08 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_side(t_s *s)
{
	if (s->turn_right == 1)
	{
		s->x_olddir = s->dirx;
		s->dirx = (s->dirx * cos(s->rs) - s->diry * sin(s->rs));
		s->diry = (s->x_olddir * sin(s->rs) + s->diry * cos(s->rs));
		s->x_oldplane = s->x_plane;
		s->x_plane = (s->x_plane * cos(s->rs) - s->y_plane * sin(s->rs));
		s->y_plane = (s->x_oldplane * sin(s->rs) + s->y_plane * cos(s->rs));
	}
	if (s->turn_left == 1)
	{
		s->x_olddir = s->dirx;
		s->dirx = s->dirx * cos(-s->rs) - s->diry * sin(-s->rs);
		s->diry = s->x_olddir * sin(-s->rs) + s->diry * cos(-s->rs);
		s->x_oldplane = s->x_plane;
		s->x_plane = s->x_plane * cos(-s->rs) - s->y_plane * sin(-s->rs);
		s->y_plane = s->x_oldplane * sin(-s->rs) + s->y_plane * cos(-s->rs);
	}
}

void	move2(t_s *s)
{
	double vx;
	double vy;

	vx = (cos(M_PI_2) * s->dirx - sin(M_PI_2) * s->diry);
	vy = (cos(M_PI_2) * s->diry + sin(M_PI_2) * s->dirx);
	if (s->move_right == 1)
	{
		if (s->map[(int)(s->posy)][(int)(s->posx + vx * s->ms * 1.5)]
		== 0)
			s->posx += vx * s->ms;
		if (s->map[(int)(s->posy + vy * s->ms * 1.5)][(int)(s->posx)]
		== 0)
			s->posy += vy * s->ms;
	}
	if (s->move_left == 1)
	{
		if (s->map[(int)(s->posy)][(int)(s->posx - vx * s->ms * 1.5)]
		== 0)
			s->posx -= vx * s->ms;
		if (s->map[(int)(s->posy - vy * s->ms * 1.5)][(int)(s->posx)]
		== 0)
			s->posy -= vy * s->ms;
	}
}

int		move(t_s *s)
{
	if (s->move_up == 1)
	{
		if (s->map[(int)(s->posy)][(int)(s->posx + s->dirx * s->ms * 1.6)] == 0)
			s->posx += s->dirx * s->ms;
		if (s->map[(int)(s->posy + s->diry * s->ms * 1.6)][(int)(s->posx)] == 0)
			s->posy += s->diry * s->ms;
	}
	if (s->move_down == 1)
	{
		if (s->map[(int)(s->posy)][(int)(s->posx - s->dirx * s->ms * 1.5)] == 0)
			s->posx -= s->dirx * s->ms;
		if (s->map[(int)(s->posy - s->diry * s->ms * 1.5)][(int)(s->posx)] == 0)
			s->posy -= s->diry * s->ms;
	}
	move2(&*s);
	move_side(&*s);
	ray_casting(&*s);
	mlx_destroy_image(s->mlx_ptr, s->img.img_ptr);
	mlx_destroy_image(s->mlx_ptr, s->img.map_ptr);
	return (0);
}
