/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luminosity_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:48 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 11:38:53 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	decode_color(int color, int *r, int *g, int *b)
{
	*r = (color & 0xFF0000) >> 16;
	*g = (color & 0x00FF00) >> 8;
	*b = color & 0x0000FF;
}

int		encode_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

double	get_luminosity(t_game *g, double dist)
{
	double d;

	d = (g->map.mx + g->map.my) / 2.0;
	return ((dist > d) ? 0 : (1.0 - dist / d));
}

int		fade(int color, double lum)
{
	int r;
	int g;
	int b;

	if (lum < 0)
		lum = 0;
	else if (lum > 1)
		lum = 1;
	decode_color(color, &r, &g, &b);
	return (encode_color((int)(r * lum), (int)(g * lum), (int)(b * lum)));
}
