/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:06:48 by mminet            #+#    #+#             */
/*   Updated: 2020/02/18 21:47:14 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}

int		ft_init(t_s *s)
{
	s->ms = 0.1;
	s->rs = 0.07;
	s->mapsize = s->winx / 5;
	if (s->winx > s->winy)
		s->mapsize = s->winy / 5;
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, s->winx, s->winy, "cub3d");
	if (s->tex[0].path == NULL)
		s->i++;
	while (s->i < 6)
	{
		if (!(s->tex[s->i].img = mlx_xpm_file_to_image(s->mlx_ptr,
		s->tex[s->i].path, &s->tex[s->i].texx, &s->tex[s->i].texy)))
			return (ft_error(ft_strjoin("Can't open : ", s->tex[s->i].path)));
		s->tex[s->i].data = (int *)mlx_get_data_addr(s->tex[s->i].img,
		&s->tex[s->i].bpp, &s->tex[s->i].size_l, &s->tex[s->i].endian);
		ft_free(s->tex[s->i].path);
		s->i++;
	}
	s->i = 0;
	while (s->i < s->nb_sprite)
		if (!(s->sprite[s->i++].test = malloc(sizeof(int) * s->winx)))
			return (0);
	return (1);
}

int		ft_error(char *str)
{
	int len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "usage", 6) == 0)
	{
		ft_putstr_fd("ERROR USAGE:\n\n		./Cub3d file.cub\n", 1);
		ft_putstr_fd("flags : -save\n\n\n", 1);
	}
	else if (ft_strncmp(str, "param", 6) == 0)
		ft_putstr_fd("\nERROR WITH SETTINGS\n\n", 1);
	else if (ft_strncmp(str, "path", 5) == 0)
	{
		ft_putstr_fd("\nERROR FAIL TO LOAD TEXTURE\n\n", 1);
		ft_putstr_fd("CHECK THE PATH TEXTURE\n\n", 1);
	}
	else if (ft_strncmp(str, "map", 4) == 0)
	{
		ft_putstr_fd("\nERROR WITH MAP 		EXAMPLE:\n\n", 1);
		ft_putstr_fd("1 1 1 1 1\n1 0 0 0 1\n1 2 0 2 1", 1);
		ft_putstr_fd("\n1 0 0 N 1\n1 1 1 1 1\n\n", 1);
	}
	else
		ft_putstr_fd(str, 1);
	exit(0);
	return (0);
}

void	ft_get_dir(t_s *s)
{
	if (s->bdir == 'N')
	{
		s->diry = -1;
		s->x_plane = -0.66;
	}
	if (s->bdir == 'S')
	{
		s->diry = 1;
		s->x_plane = 0.66;
	}
	if (s->bdir == 'E')
	{
		s->dirx = 1;
		s->y_plane = -0.66;
	}
	if (s->bdir == 'W')
	{
		s->dirx = -1;
		s->y_plane = 0.66;
	}
}

int		main(int ac, char **av)
{
	t_s		s;

	if (ac < 2 || ac > 3 || (ac == 3 && strncmp(av[2], "-save", 6) != 0))
		return (ft_error("usage"));
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".cub", 5))
		ft_error("usage");
	s.nb_sprite = 0;
	ft_parse(av[1], &s);
	ft_get_dir(&s);
	if (!ft_init(&s))
		return (0);
	if (ac == 3)
		save_bmp_file(&s);
	ray_casting(&s);
	mlx_hook(s.win_ptr, 17, 0, ft_error, "");
	mlx_hook(s.win_ptr, 2, 0, key, &s);
	mlx_hook(s.win_ptr, 3, 0, key_release, &s);
	mlx_loop_hook(s.mlx_ptr, move, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
