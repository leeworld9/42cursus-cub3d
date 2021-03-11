/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:32 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/12 01:33:02 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_game *game, int x, int y, int color)
{
	int dx;
	int dy;
	int maxwidth = TILE_SIZE * game->map.mx;
	//int maxhegiht = TILE_SIZE * game->map.my;
	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
		{
			game->mapimg.data[maxwidth * (y + dy) + (x + dx)] = color;
			dx++;
		}
		dy++;
	}
}

void	draw_squares(t_game *game)
{
	int x;
	int y;

	x = 0;
	while (x < game->map.mx)
	{
		y = 0;
		while (y < game->map.my)
		{
			if (game->map.map[x][y] == 1)
				draw_square(game, TILE_SIZE * x, TILE_SIZE * y, 0x000000FF);
			else if (game->map.map[x][y] >= 2 && game->map.map[x][y] < 50) // 50미만은 임시 NEWS 요것들 때문에 만든거.
				draw_square(game, TILE_SIZE * x, TILE_SIZE * y, 0x0000FF00);
			else
				draw_square(game, TILE_SIZE * x, TILE_SIZE * y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}

//수정필요
void	draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->mapimg.data[game->map.mx * (int)floor(y1) + (int)floor(x1)] = 0xC0C0C0;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void	draw_lines(t_game *game)
{
	int i;
	int maxwidth = TILE_SIZE * game->map.mx;
	int maxhegiht = TILE_SIZE * game->map.my;

	i = 0;
	while (i <= game->map.my)
	{
		draw_line(game, 0, TILE_SIZE * i, maxwidth, TILE_SIZE * i);
		i++;
	}
	i = 0;
	while (i <= game->map.mx)
	{
		draw_line(game, TILE_SIZE * i, 0, TILE_SIZE * i, maxhegiht);
		i++;
	}
}

void	draw_user(t_game *game)
{
	int i;
	int j;
	int x;
	int y;
	int maxwidth = TILE_SIZE * game->map.mx;
	//int maxhegiht = TILE_SIZE * game->map.my;

	x = (game->px) * TILE_SIZE;
	y = (game->py) * TILE_SIZE;
	i = 0;
	while (i < USER_SIZE)
	{
		j = 0;
		while (j < USER_SIZE)
		{
			game->mapimg.data[maxwidth * (y + i) + (x + j)] = 0xFF0000;
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int x;
	int y;
	int color;

	int maxwidth = TILE_SIZE * game->map.mx;
	int maxhegiht = TILE_SIZE * game->map.my;

	game->mapimg.img = mlx_new_image(game->mlx, maxwidth, maxhegiht);
	game->mapimg.data = (unsigned int *)mlx_get_data_addr(game->mapimg.img, &game->mapimg.bpp, &game->mapimg.line_size, &game->mapimg.endian);

	draw_squares(game);
	draw_lines(game);
	draw_user(game);
	x = 0;
	while (x < maxwidth)
	{
		y = 0;
		while (y < maxhegiht)
		{
			color = game->mapimg.data[maxwidth * y + x];
			game->img.data[game->win.winx * (y + USER_PAD) + (x + USER_PAD)] = color;
			y++;
		}
		x++;
	}
}
