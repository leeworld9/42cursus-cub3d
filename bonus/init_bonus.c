/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 08:37:39 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/15 01:22:50 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_draw_sp(t_draw_sp *dsp)
{
	dsp->x = 0;
	dsp->y = 0;
	dsp->sh = 0;
	dsp->angle = 0;
	dsp->cx = 0;
	dsp->xmin = 0;
	dsp->xmax = 0;
	dsp->txratio = 0;
	dsp->tx = 0;
	dsp->y0 = 0;
	dsp->ty = 0;
	dsp->color = 0x000000;
	dsp->lum = 0;
}

void	init_draw_wfc(t_draw_wfc *dwfc)
{
	dwfc->y0 = 0;
	dwfc->y1 = 0;
	dwfc->ystart = 0;
	dwfc->yend = 0;
	dwfc->h = 0;
	dwfc->dh = 0;
	dwfc->d_ratio = 0;
	dwfc->fx = 0;
	dwfc->fy = 0;
	dwfc->lum = 0;
}

void	init_sprite(t_sprite *sp)
{
	sp->sx = 0;
	sp->sy = 0;
	sp->dist = 0;
	sp->th = 0;
}

void	cub_init(t_game *g)
{
	g->mlx = mlx_init();
	g->win.x = 0;
	g->win.y = 0;
	g->img.d = NULL;
	g->floor.d = NULL;
	g->ceiling.d = NULL;
	g->wall_n.d = NULL;
	g->wall_e.d = NULL;
	g->wall_w.d = NULL;
	g->wall_s.d = NULL;
	g->sprite.d = NULL;
	g->nsp = 0;
	g->sparr = NULL;
	g->map.map = NULL;
	g->map.chk = 0;
	g->map.mx = 0;
	g->map.my = 0;
	g->px = 0;
	g->py = 0;
	g->th = 0;
	g->err_chk = 0;
	g->m.d = NULL;
	mlx_get_screen_size(g->mlx, &g->win.max_x, &g->win.max_y);
}

void	cub_set(t_game *g)
{
	char *tmp;

	g->img.i = mlx_new_image(g->mlx, g->win.x, g->win.y);
	tmp = mlx_get_data_addr(g->img.i, &g->img.b, &g->img.l, &g->img.e);
	g->img.d = (unsigned int*)tmp;
	g->fov_v = deg2rad(FOV) * (double)g->win.y / (double)g->win.x;
	g->pixel_per_angle = (g->win.x - 1.0) / deg2rad(FOV);
	g->angle_per_pixel = deg2rad(FOV) / (g->win.x - 1.0);
}
