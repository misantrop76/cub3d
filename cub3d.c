/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_catch_map.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 18:01:23 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/09 17:11:10 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "mlx/mlx.h"


int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int 	ft_atoi(char *str)
{
	int nbr;
	int i;

	i = 0;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (nbr);
}

int  ft_exit(int key, t_s *s)
{
	exit(0);
	return (0);
}

int		key_release(int keycode, t_s *s)
{
	if (keycode == 13 || keycode == 126)
		s->move_up = 0;
	else if (keycode == 1 || keycode == 125)
		s->move_down = 0;
	else if (keycode == 2 || keycode == 124)
		s->move_right = 0;
	else if (keycode == 0 || keycode == 123)
		s->move_left = 0;
	else if (keycode == 257 || keycode == 258)
		s->ms = 0.05;
	return (0);
}

int		key(int key, t_s *s)
{
	if (key == 53)
	{
		if (s->win_ptr && s->mlx_ptr)
			mlx_destroy_window(s->mlx_ptr, s->win_ptr);
		exit(0);
	}
	if (key == 13 || key == 126)
		s->move_up = 1;
	else if (key == 1 || key == 125)
		s->move_down = 1;
	else if (key == 2 || key == 124)
		s->move_right = 1;
	else if (key == 0 || key == 123)
		s->move_left = 1;
	else if (key == 257 || key == 258)
		s->ms = 0.1;
	return (0);
}

int		ft_countnbr(char *str)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			size++;
		i++;
	}
	return (size);
}

int ft_countline(int fd)
{
	char *line;
	int size;

	line = 0;
	size = 1;
	while (get_next_line(fd, &line))
	{
		if (ft_isdigit(line[0]))
			size++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
	return (size);
}

int	ft_parse(char *av, t_s *s)
{
	int fd;
	char *line;
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	line = NULL;
	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'R')
		{
			i += 2;
			s->WinX = ft_atoi(line + i);
			while (ft_isdigit(line[i]))
				i++;
			s->WinY = ft_atoi(line + i);
		}
		i = 0;
		if (ft_isdigit(line[0]))
		{
			s->MapX = ft_countnbr(line);
			s->MapY = ft_countline(fd);
			fd = open(av, O_RDONLY);
			if (!(s->map = malloc(sizeof(int *) * s->MapY)))
				return (0);	
			while (i < s->MapY)
			{
				if (!(s->map[i] = malloc(sizeof(int *) * s->MapX)))
					return (0);
				i++;
			}
			i = 0;
			while (get_next_line(fd, &line) && !ft_isdigit(line[0]))
			{
				free(line);
				line = NULL;
			}
			k = 0;
			while (i != s->MapY)
			{
				while (j != s->MapX)
				{
					if (ft_isdigit(line[k]))
					{
						s->map[i][j] = ft_atoi(line + k);
						j++;
					}
					else if (ft_strchr("NSOE", line[k]))
					{
						s->map[i][j] = line[k];
						j++;
					}
					k++;
				}
				free(line);
				line = NULL;
				get_next_line(fd, &line);
				k = 0;
				j = 0;
				i++;
			}
			break;
		}
		free(line);
		line = NULL;
	}
	return (0);
}

void	ft_get_pos(t_s *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	s->PosX = 0;
	s->PosY = 0;

	while (i < s->MapY)
	{
		while (j < s->MapX)
		{
			if (s->map[i][j] != 0 && s->map[i][j] != 1)
			{
				s->PosX = (double)j + .5;
				s->PosY = (double)i + .5;
				s->Bdir = s->map[i][j];
				s->map[i][j] = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_get_dir(t_s *s)
{
	if (s->Bdir == 'N')
	{
		s->dirX = 0;
		s->dirY = -1;
		s->x_plane = 0.66;
		s->y_plane = 0;
	}
	if (s->Bdir == 'S')
	{
		s->dirX = 0;
		s->dirY = 1;
		s->x_plane = -0.66;
		s->y_plane = 0;

	}
	if (s->Bdir == 'E')
	{
		s->dirX = 1;
		s->dirY = 0;
		s->x_plane = 0;
		s->y_plane = 0.66;
	}
	if (s->Bdir == 'O')
	{
		s->dirX = -1;
		s->dirY = 0;
		s->x_plane = 0;
		s->y_plane = -0.66;
	}
}
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

void	get_dist(t_s *s)
{
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
		if (s->map[s->y_map][s->x_map] > 0)
			s->hit = 1;
	}
}

void	ray_casting_init(t_s *s, int x)
{
	s->x_cam = (2 * x / (double)(s->WinX)) - 1;
	s->x_raypos = s->PosX;
	s->y_raypos = s->PosY;
	s->x_raydir = s->dirX - s->x_plane * s->x_cam;
	s->y_raydir = s->dirY - s->y_plane * s->x_cam;
	s->x_map = (int)s->x_raypos;
	s->y_map = (int)s->y_raypos;
	get_dist_init(&*s);
	get_dist(&*s);
	if (s->side == 0)
		s->walldist = (s->x_map - s->x_raypos +
				(1 - s->x_step) / 2) / s->x_raydir;
	else
		s->walldist = (s->y_map - s->y_raypos +
				(1 - s->y_step) / 2) / s->y_raydir;
}

void	draw_wall(int x, int start, int end, t_s *s)
{
	int i = 0;

	while (i < start)
	{
		s->img.data[i * s->WinX + x] = 0x3FB0E9;
		i++;
	}
	while (start < end)
	{
		s->img.data[start * s->WinX + x] = s->color;
		start++;
	}
	while (end < s->WinY)
	{
		s->img.data[end * s->WinX + x] = 0x9BABA9;
		end++;
	}
}

void	ray_casting(t_s *s)
{
	int x;

	x = 0;
	s->img.img_ptr = mlx_new_image(s->mlx_ptr, s->WinX, s->WinY);
	s->img.data = (int *)mlx_get_data_addr(s->img.img_ptr, &s->img.bpp, &s->img.size_l, &s->img.endian);
	while (x < s->WinX)
	{

		ray_casting_init(&*s, x);
		s->lineheight = (int)(s->WinY / s->walldist);
		s->start = -s->lineheight / 2 + s->WinY / 2;
		if (s->start < 0)
			s->start = 0;
		s->end = s->lineheight / 2 + s->WinY / 2;
		if (s->end >= s->WinY)
			s->end = s->WinY - 1;
		if (s->side == 1)
			s->color = 0x875202;
		else
			s->color = 0xCB7B02;
		draw_wall(x, s->start - 1, s->end, &*s);
		x++;
	}
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.img_ptr, 0, 0);
	mlx_destroy_image(s->mlx_ptr, s->img.img_ptr);
}
void	move_side(t_s *s)
{
	if (s->move_right == 1)
	{
		s->x_olddir = s->dirX;
		s->dirX = (s->dirX * cos(-s->ms) - s->dirY * sin(-s->ms));
		s->dirY = (s->x_olddir * sin(-s->ms) + s->dirY * cos(-s->ms));
		s->x_oldplane = s->x_plane;
		s->x_plane = (s->x_plane * cos(-s->ms) - s->y_plane * sin(-s->ms));
		s->y_plane = (s->x_oldplane * sin(-s->ms) + s->y_plane * cos(-s->ms));
	}
	if (s->move_left == 1)
	{
		s->x_olddir = s->dirX;
		s->dirX = s->dirX * cos(s->ms) - s->dirY * sin(s->ms);
		s->dirY = s->x_olddir * sin(s->ms) + s->dirY * cos(s->ms);
		s->x_oldplane = s->x_plane;
		s->x_plane = s->x_plane * cos(s->ms) - s->y_plane * sin(s->ms);
		s->y_plane = s->x_oldplane * sin(s->ms) + s->y_plane * cos(s->ms);
	}
}
int		move(t_s *s)
{
	if (s->move_up == 1)
	{
		if (s->map[(int)(s->PosY)][(int)(s->PosX + s->dirX * s->ms)]== 0)
			s->PosX += s->dirX * s->ms;
		if (s->map[(int)(s->PosY + s->dirY * s->ms)][(int)(s->PosX)] == 0)
			s->PosY += s->dirY * s->ms;
	}
	if (s->move_down == 1)
	{
		if (s->map[(int)(s->PosY)][(int)(s->PosX - s->dirX * s->ms)] == 0)
			s->PosX -= s->dirX * s->ms;
		if (s->map[(int)(s->PosY - s->dirY * s->ms)][(int)(s->PosX)] == 0)
			s->PosY -= s->dirY * s->ms;
	}
	move_side(&*s);
	ray_casting(&*s);
	return (0);
}

int main(int ac, char **av)
{
	t_s		s;
	int i;
	int j;

	i = 0;
	j = 0;
	s.i = 0;
	ft_parse(av[1], &s);
	ft_get_pos(&s);
	ft_get_dir(&s);
	s.move_up = 0;
	s.move_down = 0;
	s.move_right = 0;
	s.move_left = 0;
	s.ms = 0.1;
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, s.WinX, s.WinY, "cub3d");
	mlx_hook(s.win_ptr, 2, 0, key, &s);
	mlx_hook(s.win_ptr, 3, 0, key_release, &s);
	mlx_hook(s.win_ptr, 17, 0, ft_exit, &s);
	ray_casting(&s);
	mlx_loop_hook(s.mlx_ptr, move, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
