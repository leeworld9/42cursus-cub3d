/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:58 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/10 08:19:59 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		sign(double d)
{
	if (is_zero(d))
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}

double	l2dist(double x0, double y0, double x1, double y1)
{
	double dx;
	double dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

// get_wall_intersection 여기로 빼자

double	cast_single_ray(int x, t_game *game, t_wall *wall, int **visiable)
{
	double ray;
	double wdist;

	ray = (game->th + (deg2rad(FOV) / 2.0)) - (x * game->angle_per_pixel);
	if (get_wall_intersection(ray, game, wall, visiable) == false)
		return (INFINITY);
	wdist = l2dist(game->px, game->py, wall->wx, wall->wy);
	wdist *= cos(game->th - ray);
	return (wdist);
}
