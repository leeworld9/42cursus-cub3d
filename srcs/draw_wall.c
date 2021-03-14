/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:40 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 10:57:17 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_wall_height(t_game *g, double dist)
{
	double	view_h;

	view_h = 2.0 * dist * tan(g->fov_v / 2.0);
	return ((int)(g->win.y * (WALL_H / view_h)));
}

int		map_get_cell(t_game *g, int x, int y)
{
	char	c;

	if (x >= 0 && x < g->map.mx && y >= 0 && y < g->map.my)
	{
		c = g->map.map[x][y];
		if (ft_isdigit(c))
			return (c - '0');
		else
			return (c);
	}
	else
		return (-1);
}

void	draw_wall(t_game *g, double wdist, int x, int tx)
{
	t_draw_wfc	dw;
	int			wh;
	int			y;
	double		lum;
	int			ty;

	wh = get_wall_height(g, wdist);
	dw.y0 = (int)((g->win.y - wh) / 2.0);
	dw.y1 = dw.y0 + wh - 1;
	dw.ystart = max(0, dw.y0);
	dw.yend = min(g->win.y - 1, dw.y1);
	y = dw.ystart;
	while (y <= dw.yend)
	{
		lum = get_luminosity(g, wdist);
		ty = (int)((double)(y - dw.y0) * 64 / wh);
		g->img.d[g->win.x * y + x] = fade(get_wall_tex(g, tx, ty), lum);
		y++;
	}
}

int		get_wall_tex(t_game *g, int tx, int ty)
{
	int color;

	color = 0x000000;
	if (g->wall.wdir == DIR_E)
		color = g->wall_e.d[64 * ty + tx];
	else if (g->wall.wdir == DIR_W)
		color = g->wall_w.d[64 * ty + tx];
	else if (g->wall.wdir == DIR_N)
		color = g->wall_n.d[64 * ty + tx];
	else if (g->wall.wdir == DIR_S)
		color = g->wall_s.d[64 * ty + tx];
	return (color);
}
