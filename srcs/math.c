/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:54 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/08 04:13:58 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double is_zero(double d)
{
	return (fabs(d) < EPS);
}

double deg2rad(double d)
{
	return (d * M_PI / 180.0);
}

double rad2deg(double d)
{
	return (d * 180.0 / M_PI);
}

int max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

int min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}