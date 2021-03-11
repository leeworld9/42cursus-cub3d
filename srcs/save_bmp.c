/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   save_bmp.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dohelee <dohelee@student.42seoul.kr>	   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/03/09 08:49:27 by dohelee		   #+#	#+#			 */
/*   Updated: 2021/03/09 08:55:13 by dohelee		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	get_bitmapdata(t_game *game, int fd)
{
	int				i;
	int				j;
	int				ret;
	unsigned char	buffer[4];

	i = game->win.winx * (game->win.winy - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < game->win.winx)
		{
			buffer[0] = (unsigned char)(game->img.data[i]);
			buffer[1] = (unsigned char)(game->img.data[i] >> 8);
			buffer[2] = (unsigned char)(game->img.data[i] >> 16);
			buffer[3] = (unsigned char)(0);
			if ((ret = write(fd, buffer, 4)) < 0)
				printf("bmp err : write error\n");
			i++;
			j++;
		}
		i -= 2 * game->win.winx;
	}
	printf("image upload complete\n");
}

void	get_bitmapinfo(t_game *game, int fd)
{
	int				n;
	int				ret;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	header[4] = (unsigned char)(game->win.winx);
	header[5] = (unsigned char)(game->win.winx >> 8);
	header[6] = (unsigned char)(game->win.winx >> 16);
	header[7] = (unsigned char)(game->win.winx >> 24);
	header[8] = (unsigned char)(game->win.winy);
	header[9] = (unsigned char)(game->win.winy >> 8);
	header[10] = (unsigned char)(game->win.winy >> 16);
	header[11] = (unsigned char)(game->win.winy >> 24);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
	if ((ret = write(fd, header, 40)) < 0)
		printf("bmp err : write error\n");
}

void	get_bitmapfile(t_game *game, int fd)
{
	int				n;
	int				ret;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	n = game->win.winx * game->win.winy * BYTES_PER_PIXEL + FILE_HEADER_SIZE + INFO_HEADER_SIZE;
	header[2] = (unsigned char)(n);
	header[3] = (unsigned char)(n >> 8);
	header[4] = (unsigned char)(n >> 16);
	header[5] = (unsigned char)(n >> 24);
	header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	if ((ret = write(fd, header, 14)) < 0)
		printf("bmp err : write error\n");
	
}

int		get_bitmap(t_game *game, int fd)
{
	render(game);
	fd = open("cub3D.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	get_bitmapfile(game, fd);
	get_bitmapinfo(game, fd);
	get_bitmapdata(game, fd);
	close(fd);
	// free(s->img.ptr);
	// free(s->img.adr);
	//ft_close(game, 0);
	return (1);
}