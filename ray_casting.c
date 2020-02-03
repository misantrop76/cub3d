/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_casting.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:54:36 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/02 16:23:59 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void	get_dist_init(t_s *s)
{
	s->x_deltadist = sqrt(1 + (s->y_raydir * s->y_raydir)
			/ (s->x_raydir * s->x_raydir));
	s->y_deltadist = sqrt(1 + (s->x_raydir * s->x_raydir)
			/ (s->y_raydir * s->y_raydir));
	if (s->x_raydir < 0)
	{
		s->x_step = -1;
		s->x_sidedist = (s->x_raypos - s->x_map) * s->x_deltadist;
	}
	else
	{
		s->x_step = 1;
		s->x_sidedist = (s->x_map + 1.0 - s->x_raypos) * s->x_deltadist;
	}
	if (s->y_raydir < 0)
	{
		s->y_step = -1;
		s->y_sidedist = (s->y_raypos - s->y_map) * s->y_deltadist;
	}
	else
	{
		s->y_step = 1;
		s->y_sidedist = (s->y_map + 1.0 - s->y_raypos) * s->y_deltadist;
	}
}

void	get_dist(t_s *s, int x)
{
	int a = 0;

	s->hit = 0;

	while (s->hit == 0)
	{
		if (s->x_sidedist < s->y_sidedist)
		{
			s->x_sidedist += s->x_deltadist;
			s->x_map += s->x_step;
			s->side = 0;
		}
		else
		{
			s->y_sidedist += s->y_deltadist;
			s->y_map += s->y_step;
			s->side = 1;
		}
		if (s->map[s->y_map][s->x_map] == 1)
			s->hit = 1;
		a = 0;
		if (s->map[s->y_map][s->x_map] == 2)
		{
			while (a < s->nb_sprite)
			{
				if ((int)(s->sprite[a].x - 0.5) == s->x_map && (int)(s->sprite[a].y - 0.5) == s->y_map)
					break;
				a++;
			}
			s->sprite[a].test[x] = 1;
			s->sprite[a].spritex = 1;
		}
	}
}

void	ray_casting_init(t_s *s, int x)
{

	s->x_cam = (2 * x / (double)(s->winx)) - 1;
	s->x_raypos = s->posx;
	s->y_raypos = s->posy;
	s->x_raydir = s->dirx - s->x_plane * s->x_cam;
	s->y_raydir = s->diry - s->y_plane * s->x_cam;
	s->x_map = (int)s->x_raypos;
	s->y_map = (int)s->y_raypos;
	get_dist_init(&*s);
	get_dist(&*s, x);
	if (s->side == 0)
		s->walldist = (s->x_map - s->x_raypos +
				(1 - s->x_step) / 2) / s->x_raydir;
	else
		s->walldist = (s->y_map - s->y_raypos +
				(1 - s->y_step) / 2) / s->y_raydir;

}

int	ray_casting(t_s *s)
{
	int x;
	int a;

	x = 0;
	s->img.img_ptr = mlx_new_image(s->mlx_ptr, s->winx, s->winy);
	s->img.data = (int *)mlx_get_data_addr(s->img.img_ptr, &s->img.bpp, &s->img.size_l, &s->img.endian);
	s->img.map_ptr = mlx_new_image(s->mlx_ptr, s->mapsize, s->mapsize);
	s->img.mapdata = (int *)mlx_get_data_addr(s->img.map_ptr, &s->img.mapbpp, &s->img.mapsize_l, &s->img.mapendian);
	draw_map(&*s);
	a = 0;
	while (a < s->nb_sprite)
		s->sprite[a++].spritex = 0;
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
	x = 0;
	a = 0;
	ft_sprite(&*s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.img_ptr, 0, 0);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.map_ptr, 0 + 5, s->winy - s->mapsize - 5);
	mlx_destroy_image(s->mlx_ptr, s->img.img_ptr);
	mlx_destroy_image(s->mlx_ptr, s->img.map_ptr);
	a = 0;
	x = 0;
	while (a < s->nb_sprite)
	{
		while (x < s->winx)
		{
			s->sprite[a].test[x] = 0;
			x++;
		}
		x = 0;
		a++;
	}
	return (0);
}
