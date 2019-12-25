/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/16 23:02:07 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/21 00:25:37 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "paint.h"
#include "../mlx/mlx.h"
#include <stdio.h>

int		ft_convert(int r, int g, int b)
{
	int nb;

	nb = r * 65536 + g * 256 + b;
	return (nb);
}

int		aff2(int key, t_ptr *ptr)
{
	int size = ptr->size;
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < size)
	{
		while (y < size)
		{
			mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, ptr->x + x, ptr->y + y, ptr->Color);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

int		mouse(int key, int x, int y, t_ptr *ptr)
{
	int size = ptr->size;
	int a;
	int b;

	a = 0;
	b = 0;
	if (key == 4 || key == 5)
	{
		size = 3;
	}
	while (a < size)
	{
		while (b < size)
		{
			mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, x + a, y + b, ptr->color_tmp);
			b++;
		}
		b = 0;
		a++;
	}
	return (0);
}

int		aff(int key, t_ptr *ptr)
{
	int size = ptr->size;

	int x;
	int y;

	x = 0;
	y = 0;
	while (x < size)
	{
		while (y < size)
		{
			mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, ptr->x + x, ptr->y + y, ptr->color_tmp);
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;
	if (key == 126)
		ptr->y -= size;
	else if (key == 123)
		ptr->x -= size;
	else if (key == 125)
		ptr->y += size;
	else if (key == 124)
		ptr->x += size;
	else if	(key == 14)
		ptr->color_tmp = ptr->Color_font;
	else if (key == 35)
		ptr->color_tmp = ptr->Color;
	else if (key == 3)
	{
		ptr->x = 0;
		ptr->y = 0;
		while (ptr->x < ptr->WinX)
		{
			while (ptr->y < ptr->WinY)
			{
				mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, ptr->x, ptr->y, ptr->Color_font);
				ptr->y++;
			}
			ptr->y = 0;
			ptr->x++;
		}
		ptr->x = ptr->WinX / 2;
		ptr->y = ptr->WinY / 2;
	}
	else if (key == 8)
	{
		ptr->Color += 1000;
		if (ptr->Color > ft_convert(255,255,255))
			ptr->Color = 0;
		ptr->color_tmp = ptr->Color;
	}	
	else if (key >= 83 && key <= 92)
	{
		ptr->size = (key - 82) * 10;
	}
	if (key != 3)
		while (x < size)
		{
			while (y < size)
			{
				mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, ptr->x + x, ptr->y + y, ptr->color_tmp);
				y++;
			}
			y = 0;
			x++;
		}
	if (ptr->x > ptr->WinX)
		ptr->x = 0;
	if (ptr->y > ptr->WinY)
		ptr->y = 0;
	if (ptr->x < 0)
		ptr->x = ptr->WinX;
	if (ptr->y < 0)
		ptr->y = ptr->WinY;
	return (0);
}

int main()
{
	t_ptr ptr;
	
	ptr.WinX = 1920;
	ptr.WinY = 1080;
	ptr.size = 100;
	ptr.x = 0;
	ptr.y = 0;
	ptr.Color_font = ft_convert(50, 50, 50);
	ptr.Color = ft_convert(130, 138, 255);
	ptr.mlx_ptr = mlx_init();
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, ptr.WinX, ptr.WinY, "salut");
	while (ptr.x < ptr.WinX)
	{
		while (ptr.y < ptr.WinY)
		{
			mlx_pixel_put(ptr.mlx_ptr, ptr.win_ptr, ptr.x, ptr.y, ptr.Color_font);
			ptr.y++;
		}
		ptr.x++;
		ptr.y = 0;
	}
	ptr.x = ptr.WinX / 2;
	ptr.y = ptr.WinY / 2;
	ptr.color_tmp = ptr.Color;
	mlx_hook(ptr.win_ptr, 2, 0, aff, &ptr);
	mlx_hook(ptr.win_ptr, 3, 0, aff2, &ptr);
	mlx_mouse_hook(ptr.win_ptr,  mouse, &ptr);
	mlx_loop(ptr.mlx_ptr);
}
