/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:50:33 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 15:44:59 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void	move_side(t_s *s)
{
	if (s->turn_right == 1)
	{
		s->x_olddir = s->dirX;
		s->dirX = (s->dirX * cos(s->rs) - s->dirY * sin(s->rs));
		s->dirY = (s->x_olddir * sin(s->rs) + s->dirY * cos(s->rs));
		s->x_oldplane = s->x_plane;
		s->x_plane = (s->x_plane * cos(s->rs) - s->y_plane * sin(s->rs));
		s->y_plane = (s->x_oldplane * sin(s->rs) + s->y_plane * cos(s->rs));
	}
	if (s->turn_left == 1)
	{
		s->x_olddir = s->dirX;
		s->dirX = s->dirX * cos(-s->rs) - s->dirY * sin(-s->rs);
		s->dirY = s->x_olddir * sin(-s->rs) + s->dirY * cos(-s->rs);
		s->x_oldplane = s->x_plane;
		s->x_plane = s->x_plane * cos(-s->rs) - s->y_plane * sin(-s->rs);
		s->y_plane = s->x_oldplane * sin(-s->rs) + s->y_plane * cos(-s->rs);
	}
}

int		move(t_s *s)
{
	double vx;
	double vy;

	if (s->move_up == 1)
	{
		if (s->map[(int)(s->PosY)][(int)(s->PosX + s->dirX * s->ms * 1.5)] != 1 && s->map[(int)(s->PosY)][(int)(s->PosX + s->dirX * (s->ms / 1.2))] != 2)
			s->PosX += s->dirX * s->ms;
		if (s->map[(int)(s->PosY + s->dirY * s->ms * 1.5)][(int)(s->PosX)] != 1 && s->map[(int)(s->PosY + s->dirY * (s->ms / 1.2))][(int)(s->PosX)] != 2)
			s->PosY += s->dirY * s->ms;
	}
	if (s->move_down == 1)
	{
		if (s->map[(int)(s->PosY)][(int)(s->PosX - s->dirX * s->ms * 1.5)] != 1)
			s->PosX -= s->dirX * s->ms;
		if (s->map[(int)(s->PosY - s->dirY * s->ms * 1.5)][(int)(s->PosX)] != 1)
			s->PosY -= s->dirY * s->ms;
	}
	vx = (cos(M_PI_2) * s->dirX - sin(M_PI_2) * s->dirY);
	vy = (cos(M_PI_2) * s->dirY + sin(M_PI_2) * s->dirX);
	if (s->move_right == 1)
	{
		if (s->map[(int)(s->PosY)][(int)(s->PosX + vx * s->ms * 1.5)] != 1)
			s->PosX += vx * s->ms;
		if (s->map[(int)(s->PosY + vy* s->ms * 1.5)][(int)(s->PosX)] != 1)
			s->PosY += vy * s->ms;
	}
	if (s->move_left == 1)
	{
		if (s->map[(int)(s->PosY)][(int)(s->PosX - vx * s->ms * 1.5)] != 1)
			s->PosX -= vx * s->ms;
		if (s->map[(int)(s->PosY - vy* s->ms * 1.5)][(int)(s->PosX)] != 1)
			s->PosY -= vy * s->ms;
	}
	move_side(&*s);
	ray_casting(&*s);
	return (0);
}
