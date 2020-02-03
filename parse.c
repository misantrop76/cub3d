/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:21:20 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/02 16:23:24 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_get_color(char *str)
{
	int i;
	int R;
	int G;
	int B;
	i = 0;
	while (str[i] == ' ')
		i++;
	R = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i])
		i++;
	G = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	while (!ft_isdigit(str[i]) && str[i])
		i++;
	B = ft_atoi(str + i);
	if (R > 255 || G > 255 || B > 255)
		ft_error("ERROR WITH COLORS");
	i = R * 65536 + G * 256 + B;
	return (i);
}

int get_nbr_line(char *av, t_s *s)
{
	int fd;
	char *line;
	int nb;

	nb = 0;
	line = NULL;
	if (!(fd = open(av, O_RDONLY)))
		ft_error("usage");
	while (get_next_line(fd, &line))
	{
		free(line);
		line = NULL;
		nb++;
	}
	free(line);
	line = NULL;
	close(fd);
	if (!(s->str = malloc(sizeof(char *) * nb + 1)))
		return (0);
	s->str[nb] = 0;
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
	{
		if (s->str[a][i++] != '1')
			ft_error("map");
	}
	s->mapy++;
	a++;
	while (s->str[a] != 0)
	{
		i = 0;
		if ((int)ft_strlen(s->str[a]) != s->mapx)
			ft_error("map");
		if (s->str[a][0] != '1' || s->str[a][s->mapx - 1] != '1')
			ft_error("map");
		while (s->str[a][i])
		{
			if (s->str[a][i++] == '2')
				s->nb_sprite++;
		}
		a++;
		s->mapy++;
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
	i = 0;
	while (i < s->mapy)
	{
		while (j < s->mapx)
		{
			if (s->str[a][j] >= '0' && s->str[a][j] <= '2')
			{
				s->map[i][j] = s->str[a][j] - 48;
				if (s->str[a][j] == '2')
				{
					s->sprite[sp].x = (double)j + 0.5;
					s->sprite[sp].y = (double)i + 0.5;
					sp++;
				}
			}
			else if (s->str[a][j] == 'N' || s->str[a][j] == 'S' || s->str[a][j] == 'W' || s->str[a][j] == 'E')
			{
				s->map[i][j] = 0;
				s->posx = (double)j + 0.5;
				s->posy = (double)i + 0.5;
				s->d++;
				s->bdir = s->str[a][j];
			}
			j++;
		}
		j = 0;
		i++;
		a++;
	}

}

void	ft_parse_param(t_s *s)
{
	s->i = 0;
	int i;
	s->i = 0;
	while (!ft_isdigit(s->str[s->i][0]) && s->str[s->i] != 0)
	{
		i = 0;
		if (s->str[s->i][0] == 'R')
		{
			i += 2;
			s->winx = ft_atoi(s->str[s->i] + i);
			while (ft_isdigit(s->str[s->i][i]))
				i++;
			s->winy = ft_atoi(s->str[s->i] + i);
			s->R++;
		}
		else if (s->str[s->i][0] == 'N' && s->str[s->i][1] == 'O')
		{
			i += 2;
			while (s->str[s->i][i] == ' ')
				i++;
			s->tex[4].path = ft_strdup(s->str[s->i] + i);
			s->NO++;
		}
		else if (s->str[s->i][0] == 'E' && s->str[s->i][1] == 'A')
		{
			i += 2;
			while (s->str[s->i][i] == ' ')
				i++;
			s->tex[3].path = ft_strdup(s->str[s->i] + i);
			s->EA++;
		}
		else if (s->str[s->i][0] == 'S' && s->str[s->i][1] == 'O')
		{
			i += 2;
			while (s->str[s->i][i] == ' ')
				i++;
			s->tex[2].path = ft_strdup(s->str[s->i] + i);
			s->SO++;
		}
		else if (s->str[s->i][0] == 'W' && s->str[s->i][1] == 'E')
		{
			i += 2;
			while (s->str[s->i][i] == ' ')
				i++;
			s->tex[1].path = ft_strdup(s->str[s->i] + i);
			s->WE++;
		}
		else if (s->str[s->i][0] == 'C')
		{
			i += 2;
			while (s->str[s->i][i] == ' ')
				i++;
			s->tex[0].path = ft_strdup("");
			if (ft_isdigit(s->str[s->i][i]))
				s->sky_color = ft_get_color(s->str[s->i] + i);
			else
				s->tex[0].path = ft_strdup(s->str[s->i] + i);
			s->C++;
		}
		else if (s->str[s->i][0] == 'S')
		{
			i += 2;
			while (s->str[s->i][i] == ' ')
				i++;
			s->tex[5].path = ft_strdup(s->str[s->i] + i);
			s->S++;
		}
		else if (s->str[s->i][0] == 'F')
		{
			i++;
			s->floor_color = ft_get_color(s->str[s->i] + i);
			s->F++;
		}
		else if (s->str[s->i][0] != '\0')
			ft_error("param");
		s->i++;
	}
	if (s->winx > 2560)
		s->winx = 2560;
	if (s->winy > 1440)
		s->winy = 1395;
	if (s->SO != 1 || s->WE != 1 || s->NO != 1 || s->EA != 1 || s->S != 1 || s->R !=1 || s->C !=1 || s->F != 1)
		ft_error("param");
	if (ft_isdigit(s->str[s->i][0]))
		ft_parse_map(&*s, s->i);
	if (s->d != 1)
		ft_error("map");
}

int	ft_parse(char *av, t_s *s)
{
	int fd;
	char *line;
	int i;

	i = 0;
	line = NULL;
	get_nbr_line(av, &*s);
	if (!(fd = open(av, O_RDONLY)))
		return(0);
	while (get_next_line(fd, &line))
	{
		s->str[i] = ft_strdup(line);
		free(line);
		line = NULL;
		i++;
	}
	free(line);
	line = NULL;
	close(fd);
	i = 0;
	ft_parse_param(&*s);
	return (1);
}
