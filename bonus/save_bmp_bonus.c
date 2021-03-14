/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:49:28 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 12:06:00 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_bitmapdata(t_game *g, int fd)
{
	int				i;
	int				j;
	int				ret;
	unsigned char	buffer[4];

	i = g->win.x * (g->win.y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < g->win.x)
		{
			buffer[0] = (unsigned char)(g->img.d[i]);
			buffer[1] = (unsigned char)(g->img.d[i] >> 8);
			buffer[2] = (unsigned char)(g->img.d[i] >> 16);
			buffer[3] = (unsigned char)(0);
			if ((ret = write(fd, buffer, 4)) < 0)
				printf("bmp err : write error\n");
			i++;
			j++;
		}
		i -= 2 * g->win.x;
	}
	printf("Image Upload Completed\n");
}

void	get_bitmapinfo(t_game *g, int fd)
{
	int				n;
	int				ret;
	unsigned char	header[40];
	int				size;

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	header[4] = (unsigned char)(g->win.x);
	header[5] = (unsigned char)(g->win.x >> 8);
	header[6] = (unsigned char)(g->win.x >> 16);
	header[7] = (unsigned char)(g->win.x >> 24);
	header[8] = (unsigned char)(g->win.y);
	header[9] = (unsigned char)(g->win.y >> 8);
	header[10] = (unsigned char)(g->win.y >> 16);
	header[11] = (unsigned char)(g->win.y >> 24);
	header[12] = (unsigned char)(1);
	size = BYTES_PER_PIXEL * 8;
	header[14] = (unsigned char)(size);
	if ((ret = write(fd, header, 40)) < 0)
		printf("bmp err : write error\n");
}

void	get_bitmapfile(t_game *g, int fd)
{
	int				n;
	int				ret;
	int				size;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	size = (FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	n = g->win.x * g->win.y * BYTES_PER_PIXEL + size;
	header[2] = (unsigned char)(n);
	header[3] = (unsigned char)(n >> 8);
	header[4] = (unsigned char)(n >> 16);
	header[5] = (unsigned char)(n >> 24);
	header[10] = (unsigned char)(size);
	if ((ret = write(fd, header, 14)) < 0)
		printf("bmp err : write error\n");
}

int		get_bitmap(t_game *g, int fd)
{
	if (render(g) < 0)
		return (-1);
	fd = open("cub3D_bonus.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	get_bitmapfile(g, fd);
	get_bitmapinfo(g, fd);
	get_bitmapdata(g, fd);
	close(fd);
	exit(0);
	return (1);
}
