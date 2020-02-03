/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 18:02:01 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 00:38:52 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct	s_tex
{
	void		*img;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			texx;
	int			texy;
	char		*path;
}				t_tex;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
	double		xx;
	double		yy;
	double		v;
	double		vx;
	double		vy;
	int			a;
	int			b;
	int			size;
	int			spritex;
	int			*test;

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

typedef struct	s_s
{
	char				**str;
	void				*mlx_ptr;
	void				*win_ptr;
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				x_plane;
	double				y_plane;
	double				x_cam;
	double				x_raypos;
	double				y_raypos;
	double				x_raydir;
	double				y_raydir;
	double				x_sidedist;
	double				y_sidedist;
	double				x_deltadist;
	double				y_deltadist;
	double				walldist;
	double				x_olddir;
	double				x_oldplane;
	double				x_wall;
	double				ms;
	double				rs;
	int					bdir;
	int					**map;
	int					i;
	int					winx;
	int					winy;
	int					mapx;
	int					mapy;
	int					x_map;
	int					y_map;
	int					x_step;
	int					y_step;
	int					hit;
	int					side;
	int					lineheight;
	int					start;
	int					end;
	int					color;
	int					x_text;
	int					y_text;
	int					move_up;
	int					move_down;
	int					move_left;
	int					move_right;
	int					mvback;
	int					check;
	int					mapsize;
	int					turn_left;
	int					turn_right;
	int					nb_sprite;
	int					sky_color;
	int					floor_color;
	unsigned short int	NO;
	unsigned short int	SO;
	unsigned short int	EA;
	unsigned short int	WE;
	unsigned short int	S;
	unsigned short int	F;
	unsigned short int	C;
	unsigned short int	R;
	unsigned short int	d;
	t_sprite			*sprite;
	t_img				img;
	t_tex				tex[6];
}				t_s;

int				get_next_line(int fd, char **line);
int				ft_parse(char *av, t_s *s);
int				key_release(int key, t_s *s);
int				ft_exit(void);
int				key(int key, t_s *s);
int				move(t_s *s);
int				ray_casting(t_s *s);
void			draw_map(t_s *s);
void			draw_wall(int x, int start, int end, t_s *s);
void			ft_sprite(t_s *s);
int				ft_error(char *str);
void            save_bmp_file(t_s *s);

#endif
