/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_catch_map.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 18:01:23 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/22 16:19:17 by mminet      ###    #+. /#+    ###.fr     */
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

int 	ft_atoi(char *str, t_s *s)
{
	int nbr;

	nbr = 0;
	while (str[s->i] == ' ' || str[s->i] == '	')
		s->i++;
	while (ft_isdigit(str[s->i]))
	{
		nbr = nbr * 10 + (str[s->i] - 48);
		s->i++;
	}
	return (nbr);
}

int		check_map(t_s s)
{
	s.i = 0;
	while ((s.map[s.i] >= '0' && s.map[s.i] <= '3') || ft_strchr("NSEO", s.map[s.i]))
		s.i++;
	if (s.map[s.i] != '\0')
		return (0);
	s.i = 0;
	if (ft_strlen(s.map) % s.MapY != 0)
		return (0);

	return (1);
}

void	ft_putcube(int *x, int *y, t_s *s, int color)
{
	int sizex;
	int sizey;

	sizex = 100 + *x;
	sizey = 100 + *y;
	while (*y < sizey)
	{
		while (*x < sizex)
		{
			s->img.data[*y * (s->MapX * 100) + *x] = color;
			*x += 1;
		}
		*x = sizex - 100;
		*y += 1;
	}
	if (*x == (s->MapX * 100) - 100)
	{
		*x = 0;
	}
	else
	{
		*x += 100;
		*y = sizey -100;
	}
}

int		exit_hook(t_s *s)
{
	exit(0);
}

int  ft_exit(int key, t_s *s)
{
	exit(0);
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
	return (0);
}

/*void aff_line(int x1, int y1, int x2, int y2)
{
	while (x1 < x2)
	{
		
	}
}*/

int key_press(int key, t_s *s)
{
printf("hey\n");
return (0);
}

int main(int ac, char **av)
{
	int fd;
	char *line;
	t_s s;
	int x;
	int y;


	x = 0;
	y = 0;
	s.i = 0;
	s.map = NULL;
	fd = open(av[1], O_RDONLY);
	line = NULL;
	s.MapX = 0;
	s.MapY = 1;
	while (get_next_line(fd, &line) && line)
	{
		if (line[s.i] == 'R')
		{
			s.i++;
			s.WinX = ft_atoi(line, &s);
			s.WinY = ft_atoi(line, &s);
		}
		if (ft_isdigit(line[s.i]))
		{
			s.MapX = ft_strlen(line);
			s.map = ft_strjoin(s.map, line);
			s.i = 0;
			while (get_next_line(fd, &line))
			{
				s.map = ft_strjoin(s.map, line);
				s.MapY++;
			}
		}
		s.i = 0;
	}
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, s.MapX * 100, s.MapY * 100, "cub3d");
	s.img.img_ptr = mlx_new_image(s.mlx_ptr, s.MapX * 100, s.MapY * 100);
	s.img.data = (int *)mlx_get_data_addr(s.img.img_ptr, &s.img.bpp, &s.img.size_l, &s.img.endian);
	while (s.map[s.i])
	{
		if (s.map[s.i] == '1')
			ft_putcube(&x, &y, &s, 16777215);
		else
			ft_putcube(&x, &y, &s, 0);
		s.i++;
	}
	s.i = 0;
	while (!ft_strchr("NOES", s.map[s.i]))
		s.i++;
	s.PosX = s.i % s.MapX * 100 + 50;
	s.PosY = s.i / s.MapY * 100 + 50;
	s.img.data[(((s.PosY + 1) * s.MapX * 100) + (s.PosX))] = 0xFF0000;
	s.img.data[(((s.PosY + 1) * s.MapX * 100) + (s.PosX + 1))] = 0xFF0000;
	s.img.data[(s.PosY * (s.MapX * 100) + (s.PosX + 1))] = 0xFF0000;
	s.img.data[(s.PosY * (s.MapX * 100) + s.PosX)] = 0xFF0000;
	s.ray.x = 1;
	s.ray.y = 1;

//	aff_line(x1, x2, y1, y2);
	mlx_put_image_to_window(s.mlx_ptr, s.win_ptr, s.img.img_ptr, 0, 0);
	//mlx_hook(s.win_ptr, 2, (1L << 0), key_press, &s);
	mlx_hook(s.win_ptr, 2, 0, key, &s);
	mlx_hook(s.win_ptr, 17, 0, ft_exit, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
