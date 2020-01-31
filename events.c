/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   events.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:42:09 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 14:41:28 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int  ft_exit(void)
{
	
	exit(0);
}

int		key_release(int key, t_s *s)
{
	if (key == 13)
		s->move_up = 0;
	else if (key == 1)
		s->move_down = 0;
	else if (key == 2)
		s->move_right = 0;
	else if (key == 124)
		s->turn_right = 0;
	else if (key == 0)
		s->move_left = 0;
	else if (key == 123)
		s->turn_left = 0;
	else if (key == 257 || key == 258)
		s->ms = 0.1;
	return (0);
}

int		key(int key, t_s *s)
{
	if (key == 53)
		exit(0);
	if (key == 13)
		s->move_up = 1;
	else if (key == 1)
		s->move_down = 1;
	else if (key == 2)
		s->move_right = 1;
	else if (key == 124)
		s->turn_right = 1;
	else if (key == 0)
		s->move_left = 1;
	else if (key == 123)
		s->turn_left = 1;
	else if (key == 257 || key == 258)
		s->ms = 0.2;
	return (0);
}
