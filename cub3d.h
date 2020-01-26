/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 18:02:01 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 21:16:14 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
# include <math.h>

int		get_next_line(int fd, char **line);


typedef struct	s_tex
{
	void		*img;
	int			*data; 									
	int			size_l;
	int			bpp;
	int			endian;
	int			texX;
	int			texY;
}				t_tex;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
	int			a;
	int 		b;
	double		X;
	double		Y;
	double		v;
	double		vx;
	double		vy;
	int			size;
	int 		spritex;
	int *test;

}				t_sprite;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data; 									
	int			size_l;
	int			bpp;
	int			endian;
	void		*map_ptr;
	int			*mapdata; 									
	int			mapsize_l;
	int			mapbpp;
	int			mapendian;	
}				t_img;

typedef struct s_s
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		WinX;
	int		WinY;
	int 	MapX;
	int		MapY;
	double	PosX;
	double	PosY;
	int		Bdir;
	int		**map;
	int		i;
	double	dirX;
	double	dirY;
	double	x_plane;
	double	y_plane;
	int			x_map;
	int			y_map;
	int			x_step;
	int			y_step;
	int			hit;
	int			side;
	int			lineheight;
	int			start;
	int			end;
	int			color;
	double		x_cam;
	double		x_raypos;
	double		y_raypos;
	double		x_raydir;
	double		y_raydir;
	double		x_sidedist;
	double		y_sidedist;
	double		x_deltadist;
	double		y_deltadist;
	double		walldist;
	double		x_olddir;
	double		x_oldplane;
	double		x_wall;
	int			x_text;
	int			y_text;
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
	double		ms;
	double		rs;
	int			mvback;
	int			check;
	int			mapsize;
	char		*texNO;
	char		*texWE;
	char		*texEA;
	char		*texSO;
	int			turn_left;
	int			turn_right;
	int			nb_sprite;
	t_sprite 	*sprite;

	t_img	img;
	t_tex 	tex[6];
}				t_s;

#endif
