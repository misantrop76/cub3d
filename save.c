/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminet <mminet@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:08:08 by mminet            #+#    #+#             */
/*   Updated: 2020/02/24 14:51:40 by mminet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_header(unsigned char *header, int param)
{
	header[0] = (unsigned char)(param);
	header[1] = (unsigned char)(param >> 8);
	header[2] = (unsigned char)(param >> 16);
	header[3] = (unsigned char)(param >> 24);
}

void		imgbmp(t_s *s, t_bmp *bmp)
{
	int x;
	int y;
	int i;

	y = s->winy - 1;
	while (y >= 0)
	{
		x = -1;
		while (++x < s->winx)
		{
			bmp->color = 0;
			if (x < s->mapsize && y < s->mapsize)
				bmp->color = s->img.mapdata[y * s->mapsize + x];
			else
				bmp->color = s->img.data[y * s->winx + x];
			write(bmp->fd, &bmp->color, 3);
		}
		i = -1;
		while (++i < (4 - (s->winx * 3) % 4) % 4)
			write(bmp->fd, &bmp->pad, 1);
		y--;
	}
}

void		ft_header(t_s *s, t_bmp *bmp)
{
	int i;

	i = 0;
	while (i < 14)
		bmp->header[i++] = 0;
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	bmp->header[10] = 54;
	i = 0;
	while (i < 40)
		bmp->info[i++] = 0;
	bmp->info[0] = 40;
	bmp->info[12] = 1;
	bmp->info[14] = 24;
	i = 0;
	while (i < 3)
		bmp->pad[i++] = 0;
	set_header(&bmp->header[2], bmp->size);
	set_header(&bmp->info[4], s->winx);
	set_header(&bmp->info[8], s->winy);
	write(bmp->fd, bmp->header, 14);
	write(bmp->fd, bmp->info, 40);
}

void		save_bmp_file(t_s *s)
{
	t_bmp	bmp;
	int		imgsize;

	imgsize = 3 * s->winx * s->winy;
	bmp.size = 54 + imgsize;
	bmp.img = malloc((sizeof(char) * imgsize));
	ft_memset(bmp.img, 0, imgsize);
	bmp.fd = open("img.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	ft_header(s, &bmp);
	imgbmp(s, &bmp);
	free(bmp.img);
	close(bmp.fd);
	ft_exit("save", s);
}
