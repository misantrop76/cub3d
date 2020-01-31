/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 16:21:20 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 23:16:46 by mminet      ###    #+. /#+    ###.fr     */
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

int		ft_countnbr(char *str)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			size++;
		i++;
	}
	return (size);
}

int ft_countline(int fd)
{
	char *line;
	int size;

	line = 0;
	size = 1;
	while (get_next_line(fd, &line))
	{
		if (ft_isdigit(line[0]))
			size++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
	return (size);
}

int		get_mapx(char *str, t_s *s)
{
	int i;
	int lenline;

	i = 0;
	lenline = 0;
	while (str[i] == ' ' || str[i] == '1')
	{
		if (str[i] == '1')
			lenline++;
		i++;
	}
	if (str[i])
		return (0);
	s->MapX = lenline;
	return (1);
}

int ft_check_line(char *str, t_s *s)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] != '1')
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (str[i] == '2')
				s->nb_sprite++;
			len++;
		}
		else if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
		{
			s->check++;
			len++;
		}
		else if (str[i] != '\0')
			return (0);
		if (str[i] != '\0')
			i++;
	}
	if (len != s->MapX)
		return (0);
	i--;
	while (str[i] == ' ')
		i--;
	if (str[i] != '1')
		return (0);
	return (1);
}

int ft_check_map(int fd, t_s *s)
{
	char *line;

	line = NULL;
	s->MapY = 0;
	s->check = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_isdigit(line[0]))
		{
			if(!(get_mapx(line, &*s)))
				return (0);
			s->MapY++;
			break;
		}
	}
	while (get_next_line(fd, &line))
		if (line[0] == '1')
		{
			if (!ft_check_line(line, &*s))
				return (0);
			s->MapY++;
		}
	if (s->check != 1)
		return (0);
	return (1);
}

int	ft_parse(char *av, t_s *s)
{
	int fd;
	char *line;
	int i;
	int j;
	int k;
	int a;

	a = 0;
	j = 0;
	i = 0;
	line = NULL;
	
	if (!(fd = open(av, O_RDONLY)))
		return(0);
	if (!(ft_check_map(fd, &*s)))
		return (ft_error("map"));
	close(fd);
	if(!(fd = open(av, O_RDONLY)))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'R')
		{
			i += 2;
			s->WinX = ft_atoi(line + i);
			while (ft_isdigit(line[i]))
				i++;
			s->WinY = ft_atoi(line + i);
			s->R++;
		}
		else if (line[0] == 'N' && line[1] == 'O')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->tex[4].path = ft_strdup(line + i);
			s->NO++;
		}
		else if (line[0] == 'E' && line[1] == 'A')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->tex[3].path = ft_strdup(line + i);
			s->EA++;
		}
		else if (line[0] == 'S' && line[1] == 'O')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->tex[2].path = ft_strdup(line + i);
			s->SO++;
		}
		else if (line[0] == 'W' && line[1] == 'E')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->tex[1].path = ft_strdup(line + i);
			s->WE++;
		}
		else if (line[0] == 'C')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->tex[0].path = ft_strdup("");
			if (ft_isdigit(line[i]))
				s->sky_color = ft_get_color(line + i);
			else
				s->tex[0].path = ft_strdup(line + i);
			s->C++;
		}
		else if (line[0] == 'S')
		{
			i += 2;
			while (line[i] == ' ')
				i++;
			s->tex[5].path = ft_strdup(line + i);
			s->S++;
		}
		else if (line[0] == 'F')
		{
			i++;
			s->floor_color = ft_get_color(line + i);
			s->F++;
		}
		i = 0;
		if (ft_isdigit(line[0]))
		{
			if (!(s->sprite = malloc(sizeof(t_sprite) * s->nb_sprite)))
				return (0);
			if (!(s->map = malloc(sizeof(int *) * s->MapY)))
				return (0);
			while (i < s->MapY)
			{
				if (!(s->map[i] = malloc(sizeof(int) * s->MapX)))
					return (ft_error(0));
				i++;
			}
			i = 0;
			k = 0;
			while (i < s->MapY)
			{
				while (j < s->MapX && line[k])
				{
					if (line[k] >= '0' && line[k] <= '9')
					{
						s->map[i][j] = line[k] - 48;
						if (line[k] == '2')
						{
							s->sprite[a].x = (double)j + 0.5;
							s->sprite[a].y = (double)i + 0.5;
							a++;
						}
						j++;
					}
					else if (line[k] == 'N' || line[k] == 'S' || line[k] == 'W' || line[k] == 'E')
					{
						s->map[i][j] = 0;
						s->PosX = (double)j + 0.5;
						s->PosY = (double)i + 0.5;
						s->Bdir = line[k];
						j++;
					}
					k++;
				}
				get_next_line(fd, &line);
				k = 0;
				j = 0;
				i++;
			}
			j = 0;
			i--;
		}
		free(line);
		line = NULL;
	}
	j = 0;
	while (j < s->MapX)
		if (s->map[i][j++] != 1)
			return (ft_error("map"));
	close(fd);
	if (s->WinX > 2560)
		s->WinX = 2560;
	if (s->WinY > 1440)
		s->WinY = 1395;
	if (s->SO != 1 || s->WE != 1 || s->NO != 1 || s->EA != 1 || s->S != 1 || s->R !=1 || s->C !=1 || s->F != 1)
		return (ft_error("param"));
	return (1);
}