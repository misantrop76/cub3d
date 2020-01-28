/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 17:20:03 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 15:26:09 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

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

int main(int ac, char **av)
{
	t_s		s;
	int i = 1000;
	int j = 1000;
	s.i = 0;
	s.nb_sprite = 0;
	if(!(ft_parse(av[1], &s)))
		return (write(1, "map error", 9));
	ft_get_dir(&s);
	s.move_up = 0;
	s.move_down = 0;
	s.move_right = 0;
	s.move_left = 0;
	s.mvback = 0;
	s.ms = 0.1;
	s.rs = 0.07;
	s.mapsize = s.WinX / 5;
	if (s.WinX > s.WinY)
		s.mapsize = s.WinY / 5;
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, s.WinX, s.WinY, "cub3d");
	s.tex[0].img = mlx_xpm_file_to_image(s.mlx_ptr, "textures/sky2.xpm", &s.tex[0].texX, &s.tex[0].texY);
	s.tex[0].data = (int *)mlx_get_data_addr(s.tex[0].img, &s.tex[0].bpp, &s.tex[0].size_l, &s.tex[0].endian);
	s.tex[1].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texWE, &s.tex[1].texX, &s.tex[1].texY);
	s.tex[1].data = (int *)mlx_get_data_addr(s.tex[1].img, &s.tex[1].bpp, &s.tex[1].size_l, &s.tex[1].endian);
	s.tex[2].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texSO, &s.tex[2].texX, &s.tex[2].texY);
	s.tex[2].data = (int *)mlx_get_data_addr(s.tex[2].img, &s.tex[2].bpp, &s.tex[2].size_l, &s.tex[2].endian);
	s.tex[3].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texEA, &s.tex[3].texX, &s.tex[3].texY);
	s.tex[3].data = (int *)mlx_get_data_addr(s.tex[3].img, &s.tex[3].bpp, &s.tex[3].size_l, &s.tex[3].endian);
	s.tex[4].img = mlx_xpm_file_to_image(s.mlx_ptr, s.texNO, &s.tex[4].texX, &s.tex[4].texY);
	s.tex[4].data = (int *)mlx_get_data_addr(s.tex[4].img, &s.tex[4].bpp, &s.tex[4].size_l, &s.tex[4].endian);
	s.tex[5].img = mlx_xpm_file_to_image(s.mlx_ptr, "textures/barrel.xpm", &s.tex[5].texX, &s.tex[5].texY);
	s.tex[5].data = (int *)mlx_get_data_addr(s.tex[5].img, &s.tex[5].bpp, &s.tex[5].size_l, &s.tex[5].endian);
	s.i = 0;
	while (s.i < s.nb_sprite)
	{
		if (!(s.sprite[s.i].test = malloc(sizeof(int) * s.WinX)))
			return (0);
		s.i++;
	}
	i = 0;
	j = 0;
	while (i < s.nb_sprite)
	{
		while (j < s.WinX)
			s.sprite[i].test[j++] = 0;
		i++;
	}
	mlx_hook(s.win_ptr, 2, 0, key, &s);
	mlx_hook(s.win_ptr, 3, 0, key_release, &s);
	mlx_hook(s.win_ptr, 17, 0, ft_exit, &s);
	ray_casting(&s);
	mlx_loop_hook(s.mlx_ptr, move, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
