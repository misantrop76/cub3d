/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   save.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mminet <mminet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 00:19:06 by mminet       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 03:24:07 by mminet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void            write_rgb(t_s *s, int height, int width, int fd)
{
    unsigned char    abc[3];
    int                i_j[2];
    int                *img_ptr;
    unsigned char	zero[3];
    int color;
    int i = -1;
    	while (++i < 3)
		zero[i] = 0;
    int pad = (4 - (s->winx * 3) %4) % 4;
    img_ptr = (void*)s->img.img_ptr;
    i_j[0] = height;
    int x = 0;
    int y = 0;
    while (i_j[0] > 0)
    {
        i_j[1] = 0;
        while (i_j[1] < width)
        {
            color = s->img.data[i_j[0] * height + i_j[1]];
			write(fd, &color, 3);
            /*
            abc[0] = (240 & (img_ptr[(height - i_j[0]) * width + i_j[1]]) >> 16);
            abc[1] = (240 & (img_ptr[(height - i_j[0]) * width + i_j[1]]) >> 8);
            abc[2] = (240 & img_ptr[(height - i_j[0]) * width + i_j[1]]);
            write(fd, abc + 2, 1);
            write(fd, abc + 1, 1);
            write(fd, abc, 1);*/
            x++;
            if (x % 4  == 0)
                i_j[1] += 4;
        }
        if (y % 8 == 0)
            i_j[0] -= 1;
    }
}
unsigned char    *create_bitmap_file_header(int height, int width, int padding_size)
{
    int                        file_size;
    printf("%d\n", padding_size);
    static unsigned char    file_header[] = {
        0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
    file_size = 14 + 40 + (3 * width + padding_size) * height;
    file_header[0] = (unsigned char)('B');
    file_header[1] = (unsigned char)('M');
    file_header[2] = (unsigned char)(file_size);
    file_header[3] = (unsigned char)(file_size >> 8);
    file_header[4] = (unsigned char)(file_size >> 16);
    file_header[5] = (unsigned char)(file_size >> 24);
    file_header[10] = (unsigned char)(14 + 40);
    return (file_header);
}
unsigned char    *create_bitmap_info_header(int height, int width)
{
    static unsigned char info_header[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    info_header[0] = (unsigned char)(40);
    info_header[4] = (unsigned char)(width);
    info_header[5] = (unsigned char)(width >> 8);
    info_header[6] = (unsigned char)(width >> 16);
    info_header[7] = (unsigned char)(width >> 24);
    info_header[8] = (unsigned char)(height);
    info_header[9] = (unsigned char)(height >> 8);
    info_header[10] = (unsigned char)(height >> 16);
    info_header[11] = (unsigned char)(height >> 24);
    info_header[12] = (unsigned char)(1);
    info_header[14] = (unsigned char)(3 * 8);
    return (info_header);
}
void            generate_bitmap_image(t_s *s, int height, int width)
{
    int                    fd;
    unsigned char        *file_header;
    unsigned char        *info_header;
    file_header = create_bitmap_file_header(height, width, (4 - (width * 3) % 4) % 4);
    info_header = create_bitmap_info_header(height, width);
    fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00700);
    if (fd < 0)
    {
        ft_putstr_fd("Error\n", 1);
        ft_putstr_fd("Create save.bmp file.", 1);
        exit(0);
    }
    write(fd, file_header, 14);
    write(fd, info_header, 40);
    write_rgb(s, height, width, fd);
    close(fd);
}
void            save_bmp_file(t_s *s)
{
    int        height;
    int        width;
    height = s->winy;
    if (height % 2 == 1)
        height -= 1;
    width = s->winx;
    if (width % 2 == 1)
        width -= 1;
    generate_bitmap_image(s, height, width);
    exit(0);
}