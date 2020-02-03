/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:50:33 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/02 16:23:59 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_move_sprite(double posx, double posy, t_s *s)
{
	int i;

	i = 0;
	while (i < s->nb_sprite)
	{
		if (fabs(posx - s->sprite[i].x) < 0.49 &&
		fabs(posy - s->sprite[i].y) < 0.49)
			return (0);
		i++;
	}
	return (1);
}

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
		!= 1 && ft_move_sprite(s->posx + vx * s->ms, s->posy, &*s))
			s->posx += vx * s->ms;
		if (s->map[(int)(s->posy + vy * s->ms * 1.5)][(int)(s->posx)]
		!= 1 && ft_move_sprite(s->posx, s->posy + vy * s->ms, &*s))
			s->posy += vy * s->ms;
	}
	if (s->move_left == 1)
	{
		if (s->map[(int)(s->posy)][(int)(s->posx - vx * s->ms * 1.5)]
		!= 1 && ft_move_sprite(s->posx - vx * s->ms, s->posy, &*s))
			s->posx -= vx * s->ms;
		if (s->map[(int)(s->posy - vy * s->ms * 1.5)][(int)(s->posx)]
		!= 1 && ft_move_sprite(s->posx, s->posy - vy * s->ms, &*s))
			s->posy -= vy * s->ms;
	}
}

int		move(t_s *s)
{
	if (s->move_up == 1)
	{
		if (s->map[(int)(s->posy)][(int)(s->posx + s->dirx * s->ms * 1.5)] !=
		1 && ft_move_sprite(s->posx + s->dirx * s->ms, s->posy, &*s))
			s->posx += s->dirx * s->ms;
		if (s->map[(int)(s->posy + s->diry * s->ms * 1.5)][(int)(s->posx)] !=
		1 && ft_move_sprite(s->posx, s->posy + s->diry * s->ms, &*s))
			s->posy += s->diry * s->ms;
	}
	if (s->move_down == 1)
	{
		if (s->map[(int)(s->posy)][(int)(s->posx - s->dirx * s->ms * 1.5)] !=
		1 && ft_move_sprite(s->posx - s->dirx * s->ms, s->posy, &*s))
			s->posx -= s->dirx * s->ms;
		if (s->map[(int)(s->posy - s->diry * s->ms * 1.5)][(int)(s->posx)] !=
		1 && ft_move_sprite(s->posx, s->posy - s->diry * s->ms, &*s))
			s->posy -= s->diry * s->ms;
	}
	move2(&*s);
	move_side(&*s);
	ray_casting(&*s);
	return (0);
}
