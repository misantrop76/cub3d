/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 16:38:59 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 21:19:52 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

typedef struct s_ptr
{
	void *mlx_ptr;
	void *win_ptr;
	int WinX;
	int WinY;
	int Color_font;
	int Color;
	int color_tmp;
	int size;
	int x;
	int y;
	int xalea;
	int yalea;
}				t_ptr;

#endif
