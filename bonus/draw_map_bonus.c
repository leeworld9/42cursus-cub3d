/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 21:05:05 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/15 01:22:46 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_square(t_game *g, int x, int y, int color)
{
	int dx;
	int dy;
	int maxwidth;

	maxwidth = TILE_SIZE * g->map.my;
	dy = 0;
	while (dy < TILE_SIZE)
	{
		dx = 0;
		while (dx < TILE_SIZE)
		{
			g->m.d[maxwidth * (y + dy) + (x + dx)] = color;
			dx++;
		}
		dy++;
	}
}

static void	draw_squares(t_game *g)
{
	int x;
	int y;

	x = 0;
	while (x < g->map.mx)
	{
		y = 0;
		while (y < g->map.my)
		{
			if (g->map.map[x][y] == '1')
				draw_square(g, TILE_SIZE * y, TILE_SIZE * x, 0x666666);
			else if (g->map.map[x][y] == '2')
				draw_square(g, TILE_SIZE * y, TILE_SIZE * x, 0xCC3333);
			else
				draw_square(g, TILE_SIZE * y, TILE_SIZE * x, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

void		draw_user(t_game *g)
{
	int i;
	int j;
	int x;
	int y;
	int maxwidth;

	maxwidth = TILE_SIZE * g->map.my;
	y = (g->px) * TILE_SIZE;
	x = (g->py) * TILE_SIZE;
	i = 0;
	while (i < USER_SIZE)
	{
		j = 0;
		while (j < USER_SIZE)
		{
			g->m.d[maxwidth * (y + i) + (x + j)] = 0xFF0000;
			j++;
		}
		i++;
	}
}

void		draw_map(t_game *g)
{
	int		x;
	int		y;
	char	*data;
	int		maxwidth;
	int		maxhegiht;

	maxwidth = TILE_SIZE * g->map.my;
	maxhegiht = TILE_SIZE * g->map.mx;
	g->m.i = mlx_new_image(g->mlx, maxwidth, maxhegiht);
	data = mlx_get_data_addr(g->m.i, &g->m.b, &g->m.l, &g->m.e);
	g->m.d = (unsigned int *)data;
	draw_squares(g);
	draw_user(g);
	x = 0;
	while (x < maxwidth)
	{
		y = 0;
		while (y < maxhegiht)
		{
			g->m.color = g->m.d[maxwidth * y + x];
			g->img.d[g->win.x * (y + USER_PAD) + (x + USER_PAD)] = g->m.color;
			y++;
		}
		x++;
	}
}
