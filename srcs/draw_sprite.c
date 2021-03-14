/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:36 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 11:23:23 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*visspr_malloc(t_sprite *before_sparr, t_sprite sp, int n)
{
	t_sprite	*sparr;
	int			cnt;

	cnt = 0;
	sparr = NULL;
	sparr = (t_sprite*)malloc(sizeof(t_sprite) * (n));
	if (n != 1)
	{
		while (cnt < n - 1)
		{
			ft_memcpy(&sparr[cnt], &before_sparr[cnt], sizeof(t_sprite));
			cnt++;
		}
		free(before_sparr);
	}
	ft_memcpy(&sparr[n - 1], &sp, sizeof(t_sprite));
	return (sparr);
}

void		get_vis_sprites(t_game *g, t_sprite **sparr, int **vis, int *nsp)
{
	t_sprite	s;
	int			x;
	int			y;

	*nsp = 0;
	x = 0;
	while (x < g->map.mx)
	{
		y = 0;
		init_sprite(&s);
		while (y < g->map.my)
		{
			if ((vis[x][y] == 0 || map_get_cell(g, x, y) <= 1 ||
				user_dir(map_get_cell(g, x, y))) ? y++ : 0)
				continue ;
			s.sx = x;
			s.sy = y;
			s.th = atan2((y + 0.5) - g->py, (x + 0.5) - g->px);
			s.th = (s.th < 0) ? s.th + (M_PI * 2) : s.th;
			s.dist = l2dist(g->px, g->py, x + 0.5, y + 0.5) * cos(g->th - s.th);
			*sparr = visspr_malloc(*sparr, s, ++*nsp);
			y++;
		}
		x++;
	}
}

void		sort_sprite(t_sprite *sparr, int cnt)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	j = 0;
	while (i < cnt)
	{
		j = 0;
		while (j < cnt - (i + 1))
		{
			if (sparr[j].dist < sparr[j + 1].dist)
			{
				ft_memcpy(&tmp, &sparr[j + 1], sizeof(t_sprite));
				ft_memcpy(&sparr[j + 1], &sparr[j], sizeof(t_sprite));
				ft_memcpy(&sparr[j], &tmp, sizeof(t_sprite));
			}
			j++;
		}
		i++;
	}
}

void		draw_sp_texture(t_game *g, t_draw_sp *dsp, int i, double zbuf[])
{
	dsp->lum = get_luminosity(g, g->sparr[i].dist);
	dsp->x = dsp->xmin;
	while (dsp->x < dsp->xmax)
	{
		if (g->sparr[i].dist > zbuf[dsp->x] || g->sparr[i].dist < 0.2)
		{
			dsp->x++;
			continue ;
		}
		dsp->txratio = (double)(dsp->x - dsp->cx) / dsp->sh + 0.5;
		dsp->tx = (int)(dsp->txratio * g->sprite.w);
		dsp->y0 = (int)((g->win.y - dsp->sh) / 2.0);
		dsp->y = max(0, dsp->y0);
		while (dsp->y < min(g->win.y, dsp->y0 + dsp->sh))
		{
			dsp->ty = (int)((double)(dsp->y - dsp->y0) * g->sprite.h / dsp->sh);
			dsp->color = g->sprite.d[g->sprite.w * dsp->ty + dsp->tx];
			if ((dsp->color == 0x000000) ? dsp->y++ : 0)
				continue ;
			g->img.d[g->win.x * dsp->y + dsp->x] = fade(dsp->color, dsp->lum);
			dsp->y++;
		}
		dsp->x++;
	}
}

void		draw_sprites(t_game *g, int **vis, double zbuf[])
{
	t_draw_sp	dsp;
	int			i;

	init_draw_sp(&dsp);
	get_vis_sprites(g, &g->sparr, vis, &g->nsp);
	sort_sprite(g->sparr, g->nsp);
	i = 0;
	while (i < g->nsp)
	{
		dsp.sh = get_wall_height(g, g->sparr[i].dist);
		dsp.angle = g->sparr[i].th - g->th;
		if (dsp.angle > M_PI)
			dsp.angle -= (M_PI * 2);
		else if (dsp.angle < -M_PI)
			dsp.angle += (M_PI * 2);
		dsp.cx = (int)((deg2rad(FOV) / 2.0 - dsp.angle) * g->pixel_per_angle);
		dsp.xmin = max(0, dsp.cx - dsp.sh / 2);
		dsp.xmax = min(g->win.x, dsp.cx + dsp.sh / 2);
		draw_sp_texture(g, &dsp, i, zbuf);
		i++;
	}
	if (g->nsp > 0)
		free(g->sparr);
}
