/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_catch_map.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 18:01:23 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 14:58:38 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "mlx/mlx.h"
#include <stdio.h>


char	*ft_strdup1(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = (char)src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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

int		get_mapx(char *str, t_s *s)
{
	int i;
	int lenline;

	i = 0;
	lenline = 0;
	while (str[i] == ' ' || str[i] == '1')
	{
		if (str[i] == '1')
			lenline++;
		i++;
	}
	if (str[i])
		return (0);
	s->MapX = lenline;
	return (1);
}

int ft_check_line(char *str, t_s *s)
{
	int i;
	int len;

	i = 0;
	len = 0;

	while (str[i] == ' ')
		i++;
	if (str[i] != '1')
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
			len++;
		else if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
		{
			s->check++;
			len++;
		}
		else if (str[i] != '\0')
			return (0);
		if (str[i] != '\0')
			i++;
	}
	if (len != s->MapX)
		return (0);
	i--;
	while (str[i] == ' ')
		i--;
	if (str[i] != '1')
		return (0);
	return (1);
}

int ft_check_map(int fd, t_s *s)
{
	char *line;
	int i;

	line = NULL;
	s->MapY = 0;
	s->check = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_isdigit(line[0]))
		{
			if(!(get_mapx(line, &*s)))
				return (printf("error1\n"));
			s->MapY++;
			break;
		}	
	}	
	while (get_next_line(fd, &line))
		if (line[0] == '1')
		{
			if (!ft_check_line(line, &*s))
				return (0);
			s->MapY++;
		}
	if (s->check != 1)
		return (0);
	return (1);
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
	if (!(ft_check_map(fd, &*s)))
		return (0);
	close(fd);
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
		if (line[0] == 'N' && line[1] == 'O')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->texNO = ft_strdup1(line + i);
		}
		if (line[0] == 'E' && line[1] == 'A')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->texEA = ft_strdup1(line + i);
		}
		if (line[0] == 'S' && line[1] == 'O')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->texSO = ft_strdup1(line + i);
		}
		if (line[0] == 'W' && line[1] == 'E')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->texWE = ft_strdup1(line + i);
		}
		i = 0;
		if (ft_isdigit(line[0]))
		{
			if (!(s->map = malloc(sizeof(int *) * s->MapY)))
				return (0);	
			while (i < s->MapY)
			{
				if (!(s->map[i] = malloc(sizeof(int) * s->MapX)))
					return (0);
				i++;
			}
			i = 0;
			k = 0;
			while (i != s->MapY)
			{
				while (j != s->MapX)
				{
					if (line[k] >= '0' && line[k] <= '9')
					{
						s->map[i][j] = line[k] - 48;
						j++;
					}
					else if (line[k] == 'N' || line[k] == 'S' || line[k] == 'W' || line[k] == 'E')
					{
						s->map[i][j] = 0;
						s->PosX = (double)j + 0.5;
						s->PosY = (double)i + 0.5;
						s->Bdir = line[k];
						j++;
					}
					k++;
				}
				get_next_line(fd, &line);
				k = 0;
				j = 0;
				i++;
			}
			j = 0;
			i--;
		}
		free(line);
		line = NULL;
	}
	j = 0;
	while (j < s->MapX)
		if (s->map[i][j++] != 1)
			return (0);
	close(fd);
	if (s->WinX > 2560)
		s->WinX = 2560;
	if (s->WinY > 1440)
		s->WinY = 1440;
	return (1);

}

void	ft_get_dir(t_s *s)
{
	if (s->Bdir == 'N')
	{
		s->dirX = 0;
		s->dirY = -1;
		s->x_plane = -0.66;
		s->y_plane = 0;
	}
	if (s->Bdir == 'S')
	{
		s->dirX = 0;
		s->dirY = 1;
		s->x_plane = 0.66;
		s->y_plane = 0;

	}
	if (s->Bdir == 'E')
	{
		s->dirX = 1;
		s->dirY = 0;
		s->x_plane = 0;
		s->y_plane = -0.66;
	}
	if (s->Bdir == 'W')
	{
		s->dirX = -1;
		s->dirY = 0;
		s->x_plane = 0;
		s->y_plane = 0.66;
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
	int j = 0;
	double step;
	double texpos;
	int id;

	if (s->side == 0 && s->x_raydir < 0)
		id = 1;
	else if (s->side == 0)
		id = 3;
	if (s->side == 1 && s->y_raydir > 0)
		id = 2;
	else if (s->side == 1)
		id = 4;
	if (s->side == 0)
		s->x_wall = s->y_raypos + s->walldist * s->y_raydir;
	else
		s->x_wall = s->x_raypos + s->walldist * s->x_raydir;
	s->x_text = (int)(s->x_wall * (double)64);
	if (s->side == 0 && s->x_raydir > 0)
		s->x_text = 64 - s->x_text - 1;
	if (s->side == 1 && s->y_raydir < 0)
		s->x_text = 64 - s->x_text - 1;
	s->x_text = abs(s->x_text);
	texpos = (start - s->WinY / 2 + s->lineheight / 2) * step;
	while (i < start)
	{
		s->img.data[i * s->WinX + x] = s->tex[0].data[j * s->tex[0].texX + x + s->mvback];
		i++;
		j++;
		if (j  >= s->tex[0].texX)
			j = 0;
	}
	start += 2;
	while (start < end)
	{
		if (x < s->WinX && start < s->WinY)
		{
			s->y_text = abs((((start * 256 - s->WinY * 128 + s->lineheight * 128) * 64) / s->lineheight) / 256);
			s->img.data[start * s->WinX + x] = s->tex[id].data[(s->y_text % 64 * s->tex[id].size_l + s->x_text % 64 * s->tex[id].bpp /8) / 4];
			//s->img.data[start * s->WinX + x] = s->color;
			start++;
		}
	}
	while (end < s->WinY)
	{
		s->img.data[end * s->WinX + x] = 0x2A2B35;
		end++;
	}
}

int 	draw_map(t_s *s)
{
	int x = 0;
	int y = 0;
	double i;
	double j;

	x = s->mapsize / 2;
	y = s->mapsize / 2;
	s->img.mapdata[y * s->mapsize + x] = 0xFF0000;
	s->img.mapdata[(y - 1) * s->mapsize + (x - 1)] = 0xFF0000;
	s->img.mapdata[(y - 1) * s->mapsize + x] = 0xFF0000;
	s->img.mapdata[(y - 1) * s->mapsize + (x + 1)] = 0xFF0000;
	s->img.mapdata[y * s->mapsize + (x - 1)] = 0xFF0000;
	s->img.mapdata[y * s->mapsize + (x + 1)] = 0xFF0000;
	s->img.mapdata[(y + 1) * s->mapsize + (x - 1)] = 0xFF0000;
	s->img.mapdata[(y + 1) * s->mapsize + x] = 0xFF0000;
	s->img.mapdata[(y + 1) * s->mapsize + (x + 1)] = 0xFF0000;

	x = 0;
	y = 0;
	i = s->PosY - 10;
	j = s->PosX - 10;
	while (x < s->mapsize)
	{
		s->img.mapdata[y * s->mapsize + x] = 0xFFFFFF;
		x++;
	}
	x--;
	while (y < s->mapsize)
		s->img.mapdata[y++ * s->mapsize + x] = 0xFFFFFF;
	y--;
	while (x > 0)
		s->img.mapdata[y * s->mapsize + x--] = 0xFFFFFF;
	while (y > 0)
		s->img.mapdata[y-- * s->mapsize + x] = 0xFFFFFF;
	while (y < s->mapsize)
	{
		while (x < s->mapsize)
		{
			if (i >= 0 && j >= 0 && i <= (double)s->MapY && j <= (double)s->MapX && s->map[(int)i][(int)j] == 1)
				s->img.mapdata[y * s->mapsize + x] = 0xFFFFFF;
			j = j + (20.0 / s->mapsize);
			x++;
		}
		j = s->PosX - 10.0;
		i = i + (20.0 / s->mapsize);
		y++;
		x = 0;
	}
	return (0);

}

void	ray_casting(t_s *s)
{
	int x;

	x = 0;
	s->img.img_ptr = mlx_new_image(s->mlx_ptr, s->WinX, s->WinY);
	s->img.data = (int *)mlx_get_data_addr(s->img.img_ptr, &s->img.bpp, &s->img.size_l, &s->img.endian);
	s->img.map_ptr = mlx_new_image(s->mlx_ptr, s->mapsize, s->mapsize);
	s->img.mapdata = (int *)mlx_get_data_addr(s->img.map_ptr, &s->img.mapbpp, &s->img.mapsize_l, &s->img.mapendian);
	draw_map(&*s);
	if (s->move_right == 1)
		s->mvback += 50;
	if (s->move_left == 1)
		s->mvback -= 50;
	if (s->mvback + x > 3000)
		s->mvback = 0;
	if (s->mvback + x < 0)
		s->mvback = 3000 - x;

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
			s->color = 0x2D27E1;
		else
			s->color = 0x546AF7;
		draw_wall(x, s->start - 1, s->end, &*s);
		x++;
	}
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.img_ptr, 0, 0);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img.map_ptr, 0, 0);
	mlx_destroy_image(s->mlx_ptr, s->img.img_ptr);
	mlx_destroy_image(s->mlx_ptr, s->img.map_ptr);
}
void	move_side(t_s *s)
{
	if (s->move_right == 1)
	{
		s->x_olddir = s->dirX;
		s->dirX = (s->dirX * cos(s->rs) - s->dirY * sin(s->rs));
		s->dirY = (s->x_olddir * sin(s->rs) + s->dirY * cos(s->rs));
		s->x_oldplane = s->x_plane;
		s->x_plane = (s->x_plane * cos(s->rs) - s->y_plane * sin(s->rs));
		s->y_plane = (s->x_oldplane * sin(s->rs) + s->y_plane * cos(s->rs));
	}
	if (s->move_left == 1)
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
	int i = 1000;
	int j = 1000;
	s.i = 0;
	if(!(ft_parse(av[1], &s)))
		return (write(1, "map error", 9));
	printf("x = %f|y = %f|Winx = %d|winy = %d\n", s.PosX, s.PosY, s.WinX, s.WinY);
	ft_get_dir(&s);
	s.move_up = 0;
	s.move_down = 0;
	s.move_right = 0;
	s.move_left = 0;
	s.mvback = 0;
	s.ms = 0.1;
	s.rs = 0.07;
	printf("%s\n", s.texNO);
	s.mapsize = s.WinX / 5;
	if (s.WinX > s.WinY)
		s.mapsize = s.WinY / 5;
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, s.WinX, s.WinY, "cub3d");
	s.tex[0].img = mlx_xpm_file_to_image(s.mlx_ptr, "sky2.xpm", &s.tex[0].texX, &s.tex[0].texY);
	s.tex[0].data = (int *)mlx_get_data_addr(s.tex[0].img, &s.tex[0].bpp, &s.tex[0].size_l, &s.tex[0].endian);
	s.tex[1].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texWE, &i, &j);
	s.tex[1].data = (int *)mlx_get_data_addr(s.tex[1].img, &s.tex[1].bpp, &s.tex[1].size_l, &s.tex[1].endian);
	s.tex[2].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texSO, &i, &j);
	s.tex[2].data = (int *)mlx_get_data_addr(s.tex[2].img, &s.tex[2].bpp, &s.tex[2].size_l, &s.tex[2].endian);
	s.tex[3].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texEA, &i, &j);
	s.tex[3].data = (int *)mlx_get_data_addr(s.tex[3].img, &s.tex[3].bpp, &s.tex[3].size_l, &s.tex[3].endian);
	s.tex[4].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texNO, &i, &j);
	s.tex[4].data = (int *)mlx_get_data_addr(s.tex[4].img, &s.tex[4].bpp, &s.tex[4].size_l, &s.tex[4].endian);
	mlx_hook(s.win_ptr, 2, 0, key, &s);
	mlx_hook(s.win_ptr, 3, 0, key_release, &s);
	mlx_hook(s.win_ptr, 17, 0, ft_exit, &s);
	ray_casting(&s);
	mlx_loop_hook(s.mlx_ptr, move, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
