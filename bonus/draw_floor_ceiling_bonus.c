/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:21:18 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 13:00:02 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_floor_ceiling(t_game *g, double wdist, int x)
{
	t_draw_wfc	wfc;
	int			wh;
	int			y;

	init_draw_wfc(&wfc);
	wh = get_wall_height(g, wdist);
	wfc.y0 = (int)((g->win.y - wh) / 2.0);
	wfc.y1 = wfc.y0 + wh - 1;
	if (wfc.y1 < g->win.y - 1)
	{
		y = wfc.y1 + 1;
		while (y < g->win.y)
		{
			wfc.h = (double)(g->win.y - 1 - y) / g->win.y;
			wfc.dh = (WALL_H / (2.0 * tan(g->fov_v / 2))) / (1.0 - (2 * wfc.h));
			wfc.lum = get_luminosity(g, wfc.dh);
			wfc.d_ratio = wfc.dh / wdist;
			wfc.fx = g->px + (g->wall.wx - g->px) * wfc.d_ratio;
			wfc.fy = g->py + (g->wall.wy - g->py) * wfc.d_ratio;
			draw_f_texture(g, &wfc, x, y);
			draw_c_texture(g, &wfc, x, y);
			y++;
		}
	}
}

void	draw_f_texture(t_game *g, t_draw_wfc *wfc, int x, int y)
{
	int tx;
	int ty;
	int color;

	tx = (int)((wfc->fx - floor(wfc->fx)) * g->floor.w);
	ty = (int)((wfc->fy - floor(wfc->fy)) * g->floor.h);
	color = g->floor.d[g->floor.w * ty + tx];
	g->img.d[g->win.x * y + x] = fade(color, wfc->lum);
}

void	draw_c_texture(t_game *g, t_draw_wfc *wfc, int x, int y)
{
	int tx;
	int ty;
	int color;

	tx = (int)((wfc->fx - floor(wfc->fx)) * g->ceiling.w);
	ty = (int)((wfc->fy - floor(wfc->fy)) * g->ceiling.h);
	color = g->ceiling.d[g->ceiling.w * ty + tx];
	g->img.d[g->win.x * (g->win.y - 1 - y) + x] = fade(color, wfc->lum);
}
