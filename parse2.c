/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:07:41 by mminet            #+#    #+#             */
/*   Updated: 2020/02/24 17:35:08 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_get_color(char *str, t_s *s)
{
	int i;
	int r;
	int g;
	int b;

	i = 0;
	while (str[i] == ' ')
		i++;
	r = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	g = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	jump_space(str, i, 1, s);
	b = ft_atoi(str + i);
	if (r > 255 || g > 255 || b > 255)
		ft_exit("ERROR WITH COLORS", s);
	i = r * 65536 + g * 256 + b;
	return (i);
}

void	ft_parse_map2(t_s *s, int *sp, int a, int i)
{
	int j;

	j = -1;
	while (++j < s->mapx)
	{
		if (s->str[a][j] >= '0' && s->str[a][j] <= '2')
		{
			s->map[i][j] = s->str[a][j] - 48;
			if (s->str[a][j] == '2')
			{
				s->sprite[*sp].x = (double)j + 0.5;
				s->sprite[*sp].y = (double)i + 0.5;
				*sp += 1;
			}
		}
		else if (strchr("NWES", s->str[a][j]) && (s->d += 1) &&
		(s->bdir = s->str[a][j]))
		{
			s->map[i][j] = 0;
			s->posx = (double)j + 0.5;
			s->posy = (double)i + 0.5;
		}
		else
			ft_exit("map", s);
	}
}

void	ft_parse_param2(t_s *s, int i)
{
	if (s->str[s->i][0] == 'R')
	{
		i += 2;
		s->winx = ft_atoi(s->str[s->i] + i);
		i = jump_space(s->str[s->i], i, 0, s);
		s->winy = ft_atoi(s->str[s->i] + i);
		jump_space(s->str[s->i], i, 1, s);
		s->r++;
	}
	if (s->str[s->i][0] == 'N' && s->str[s->i][1] == 'O')
	{
		i += 2;
		while (s->str[s->i][i] == ' ')
			i++;
		s->tex[4].path = ft_strdup(s->str[s->i] + i);
		s->no++;
	}
	if (s->str[s->i][0] == 'E' && s->str[s->i][1] == 'A')
	{
		i += 2;
		while (s->str[s->i][i] == ' ')
			i++;
		s->tex[3].path = ft_strdup(s->str[s->i] + i);
		s->ea++;
	}
}

void	ft_parse_param3(t_s *s, int i)
{
	if (s->str[s->i][0] == 'S' && s->str[s->i][1] == 'O')
	{
		i += 2;
		while (s->str[s->i][i] == ' ')
			i++;
		s->tex[2].path = ft_strdup(s->str[s->i] + i);
		s->so++;
	}
	else if (s->str[s->i][0] == 'S')
	{
		i += 2;
		while (s->str[s->i][i] == ' ')
			i++;
		s->tex[5].path = ft_strdup(s->str[s->i] + i);
		s->s++;
	}
	if (s->str[s->i][0] == 'W' && s->str[s->i][1] == 'E')
	{
		i += 2;
		while (s->str[s->i][i] == ' ')
			i++;
		s->tex[1].path = ft_strdup(s->str[s->i] + i);
		s->we++;
	}
}

void	ft_parse_param4(t_s *s, int i)
{
	if (s->str[s->i][0] == 'C')
	{
		i += 2;
		while (s->str[s->i][i] == ' ')
			i++;
		if (ft_isdigit(s->str[s->i][i]))
			s->sky_color = ft_get_color(s->str[s->i] + i, s);
		else
			s->tex[0].path = ft_strdup(s->str[s->i] + i);
		s->c++;
	}
	if (s->str[s->i][0] == 'F')
	{
		i++;
		s->floor_color = ft_get_color(s->str[s->i] + i, s);
		s->f++;
	}
	if (!strchr("NSWECRF", s->str[s->i][0]) && s->str[s->i][0] != '\0')
		ft_exit("param", s);
	s->i++;
}
