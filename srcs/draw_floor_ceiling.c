/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:21:18 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 10:56:51 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			draw_floor_ceiling(t_game *g, double wdist, int x)
{
	t_draw_wfc	dfc;
	int			wh;
	double		lum;
	int			y;
	int			color;

	init_draw_wfc(&dfc);
	wh = get_wall_height(g, wdist);
	dfc.y0 = (int)((g->win.y - wh) / 2.0);
	dfc.y1 = dfc.y0 + wh - 1;
	if (dfc.y1 < g->win.y - 1)
	{
		y = dfc.y1 + 1;
		while (y < g->win.y)
		{
			dfc.h = (double)(g->win.y - 1 - y) / g->win.y;
			dfc.dh = (WALL_H / (2.0 * tan(g->fov_v / 2))) / (1.0 - (2 * dfc.h));
			lum = get_luminosity(g, dfc.dh);
			color = fade(g->ceiling.color, lum);
			g->img.d[g->win.x * (g->win.y - 1 - y) + x] = color;
			color = fade(g->floor.color, lum);
			g->img.d[g->win.x * y + x] = color;
			y++;
		}
	}
}
