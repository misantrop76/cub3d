/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:07:31 by mminet            #+#    #+#             */
/*   Updated: 2020/03/10 21:01:22 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_nbr_line(char *av, t_s *s)
{
	int		fd;
	char	*line;
	int		nb;

	nb = 0;
	line = NULL;
	if (!(fd = open(av, O_RDONLY)) || fd < 0)
		ft_exit("usage", s);
	while (get_next_line(fd, &line))
	{
		ft_free(line);
		nb++;
	}
	ft_free(line);
	close(fd);
	if (!(s->str = malloc(sizeof(char *) * nb + 1)))
		return (0);
	s->str[nb] = NULL;
	if (nb < 3)
		ft_exit("param", s);
	return (nb);
}

void	get_map_info(t_s *s, int a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s->str[a][i])
		if (s->str[a][i++] != '1')
			ft_exit("map", s);
	while ((s->mapy += 1) && s->str[++a] != 0)
	{
		i = -1;
		check_line(s, a);
		if (s->str[a][0] != '1' || s->str[a][ft_strlen(s->str[a]) - 1] != '1')
			ft_exit("map", s);
		while (s->str[a][++i])
			if (s->str[a][i] == '2')
				s->nb_sprite++;
			else if (!(ft_strchr("120NSEW", s->str[a][i])))
				ft_exit("map", s);
	}
	a--;
	i = 0;
	while (s->str[a][i])
		if (s->str[a][i++] != '1')
			ft_exit("map", s);
}

void	ft_parse_map(t_s *s, int a)
{
	int i;
	int j;
	int sp;

	sp = 0;
	i = 0;
	j = 0;
	get_map_info(&*s, a);
	if (!(s->sprite = malloc(sizeof(t_sprite) * s->nb_sprite)))
		ft_exit("", s);
	if (!(s->map = malloc(sizeof(char *) * s->mapy + 1)))
		ft_exit("", s);
	while (i < s->mapy)
	{
		if (!(s->map[i] = malloc(sizeof(char) * ft_strlen(s->str[a + i]) + 1)))
			ft_exit("", s);
		i++;
	}
	i = -1;
	while (++i < s->mapy)
		ft_parse_map2(s, &sp, a++, i);
	s->map[i] = 0;
}

void	ft_parse_param(t_s *s)
{
	int i;

	s->i = 0;
	while (s->str[s->i] != 0 && (!ft_isdigit(s->str[s->i][0])))
	{
		i = 0;
		ft_parse_param2(s, i);
		ft_parse_param3(s, i);
		ft_parse_param4(s, i);
	}
	if (s->winx > 2560)
		s->winx = 2560;
	if (s->winy > 1440)
		s->winy = 1395;
	if (s->so != 1 || s->we != 1 || s->no != 1 || s->ea != 1 || s->s != 1
	|| s->r != 1 || s->c != 1 || s->f != 1 || s->winx <= 0 || s->winy <= 0)
		ft_exit("param", s);
	if (s->str[s->i] != 0 && ft_isdigit(s->str[s->i][0]))
		ft_parse_map(&*s, s->i);
	if (s->d != 1)
		ft_exit("map", s);
}

void	ft_parse(char *av, t_s *s)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	get_nbr_line(av, &*s);
	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (ismap(line))
			s->str[i] = ft_strcut(line);
		else
			s->str[i] = ft_strtrim(line, " ");
		ft_free(line);
		i++;
	}
	ft_free(line);
	s->str[i] = 0;
	close(fd);
	ft_parse_param(&*s);
}
