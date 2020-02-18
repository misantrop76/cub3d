/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:07:31 by mminet            #+#    #+#             */
/*   Updated: 2020/02/18 21:43:14 by mminet           ###   ########lyon.fr   */
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
		ft_error("usage");
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
	return (nb);
}

void	get_map_info(t_s *s, int a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	s->mapx = ft_strlen(s->str[a]);
	while (s->str[a][i])
		if (s->str[a][i++] != '1')
			ft_error("map");
	while ((s->mapy += 1) && s->str[++a] != 0)
	{
		i = 0;
		if ((int)ft_strlen(s->str[a]) != s->mapx)
			ft_error("map");
		if (s->str[a][0] != '1' || s->str[a][s->mapx - 1] != '1')
			ft_error("map");
		while (s->str[a][i])
			if (s->str[a][i++] == '2')
				s->nb_sprite++;
	}
	a--;
	i = 0;
	while (s->str[a][i])
		if (s->str[a][i++] != '1')
			ft_error("map");
}

void	ft_parse_map(t_s *s, int a)
{
	int i;
	int j;
	int sp;

	sp = 0;
	i = 0;
	j = 0;
	s->i = 0;
	get_map_info(&*s, a);
	if (!(s->sprite = malloc(sizeof(t_sprite) * s->nb_sprite)))
		ft_error("");
	if (!(s->map = malloc(sizeof(int *) * s->mapy)))
		ft_error("");
	while (i < s->mapy)
	{
		if (!(s->map[i] = malloc(sizeof(int) * s->mapx)))
			ft_error("");
		i++;
	}
	i = -1;
	while (++i < s->mapy)
		ft_parse_map2(s, &sp, a++, i);
}

void	ft_parse_param(t_s *s)
{
	int i;

	s->i = 0;
	while (!ft_isdigit(s->str[s->i][0]) && s->str[s->i] != 0)
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
		ft_error("param");
	if (ft_isdigit(s->str[s->i][0]))
		ft_parse_map(&*s, s->i);
	if (s->d != 1)
		ft_error("map");
}

void	ft_parse(char *av, t_s *s)
{
	int		fd;
	char	*line;
	int		i;

	s->tex[0].path = NULL;
	i = 0;
	line = NULL;
	get_nbr_line(av, &*s);
	if (!(fd = open(av, O_RDONLY)))
		ft_error("USAGE");
	while (get_next_line(fd, &line))
	{
		s->str[i] = ft_strdup(line);
		ft_free(line);
		i++;
	}
	ft_free(line);
	close(fd);
	ft_parse_param(&*s);
}
