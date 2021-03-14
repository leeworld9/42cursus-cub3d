/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:58 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/13 04:48:01 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_ray_variable(double ray, t_game *g, t_ray *r)
{
	r->xstep = sign(cos(ray));
	r->ystep = sign(sin(ray));
	r->xslope = (r->xstep == 0) ? INFINITY : tan(ray);
	r->yslope = (r->ystep == 0) ? INFINITY : 1.0 / tan(ray);
	r->fx = INFINITY;
	r->gx = INFINITY;
	r->hit = false;
	if (r->xstep > 0)
		r->nx = floor(g->px) + 1;
	else if (r->xstep < 0)
		r->nx = ceil(g->px) - 1;
	else
		r->nx = g->px;
	if (r->ystep > 0)
		r->ny = floor(g->py) + 1;
	else if (r->ystep < 0)
		r->ny = ceil(g->py) - 1;
	else
		r->ny = g->py;
}

bool		get_wall_intersection(double ray, t_game *g, int **vis)
{
	t_ray	r;

	set_ray_variable(ray, g, &r);
	while (!r.hit)
	{
		if (r.xstep != 0)
			r.fx = r.xslope * (r.nx - g->px) + g->py;
		if (r.ystep != 0)
			r.gx = r.yslope * (r.ny - g->py) + g->px;
		r.hs = find_hitmap(g, &r, &r.mapx, &r.mapy);
		if (map_get_cell(g, r.mapx, r.mapy) < 0)
			break ;
		if (map_get_cell(g, r.mapx, r.mapy) == 1)
		{
			r.hit = hit_location(g, &r);
			break ;
		}
		vis[r.mapx][r.mapy] = 1;
		if (r.hs == VERT)
			r.nx += r.xstep;
		else
			r.ny += r.ystep;
	}
	return (r.hit);
}

t_hitside	find_hitmap(t_game *g, t_ray *r, int *mapx, int *mapy)
{
	double		dist_v;
	double		dist_h;
	t_hitside	hs;

	dist_v = l2dist(g->px, g->py, r->nx, r->fx);
	dist_h = l2dist(g->px, g->py, r->gx, r->ny);
	if (dist_v < dist_h)
	{
		*mapx = (r->xstep == 1) ? (int)(r->nx) : (int)(r->nx) - 1;
		*mapy = (int)r->fx;
		hs = VERT;
	}
	else
	{
		*mapx = (int)r->gx;
		*mapy = (r->ystep == 1) ? (int)(r->ny) : (int)(r->ny) - 1;
		hs = HORIZ;
	}
	return (hs);
}

bool		hit_location(t_game *g, t_ray *r)
{
	if (r->hs == VERT)
	{
		g->wall.wdir = (r->xstep > 0) ? DIR_W : DIR_E;
		g->wall.wx = r->nx;
		g->wall.wy = r->fx;
	}
	else
	{
		g->wall.wdir = (r->ystep > 0) ? DIR_S : DIR_N;
		g->wall.wx = r->gx;
		g->wall.wy = r->ny;
	}
	return (true);
}

double		cast_single_ray(int x, t_game *g, int **visiable)
{
	double ray;
	double wdist;

	ray = (g->th + (deg2rad(FOV) / 2.0)) - (x * g->angle_per_pixel);
	if (get_wall_intersection(ray, g, visiable) == false)
		return (INFINITY);
	wdist = l2dist(g->px, g->py, g->wall.wx, g->wall.wy);
	wdist *= cos(g->th - ray);
	return (wdist);
}
