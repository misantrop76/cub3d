/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 18:02:01 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/21 18:31:33 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		get_next_line(int fd, char **line);

typedef struct	s_img
{
	void		*img_ptr;
	int			*data; 									
	int			size_l;
	int			bpp;
	int			endian;	
}				t_img;

typedef struct	s_ray
{
	double x;
	double y;
	double w;
	double v;
}				t_ray;

typedef struct s_s
{
	void *mlx_ptr;
	void *win_ptr;
	int WinX;
	int WinY;
	int MapX;
	int MapY;
	int	 PosX;
	int	 PosY;
	char *map;
	int i;
	t_img	img;
	t_ray   ray;
}				t_s;

#endif
