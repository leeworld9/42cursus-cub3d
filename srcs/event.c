/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:45 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 10:25:50 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_game *g)
{
	int dir;

	if (key < 0 || key == KEY_ESC)
		exit(0);
	if (key == KEY_W || key == KEY_A ||
		key == KEY_S || key == KEY_D)
	{
		if (player_move(g, key) == 0)
		{
			if (render(g) < 0)
				return (-1);
		}
	}
	if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (key == KEY_LEFT)
			dir = 1;
		else
			dir = -1;
		player_rotate(g, ROTATE_UNIT * dir);
		if (render(g) < 0)
			return (-1);
	}
	return (0);
}

int		button_exit(void)
{
	exit(0);
	return (0);
}

int		move_offset(double th, int key, double *pdx, double *pdy)
{
	int dir;

	if (key == KEY_W || key == KEY_S)
	{
		if (key == KEY_W)
			dir = 1;
		else
			dir = -1;
		*pdx = dir * MOVE_UNIT * cos(th);
		*pdy = dir * MOVE_UNIT * sin(th);
	}
	else if (key == KEY_A || key == KEY_D)
	{
		if (key == KEY_A)
			dir = 1;
		else
			dir = -1;
		*pdx = MOVE_UNIT * cos(th + dir * M_PI_2);
		*pdy = MOVE_UNIT * sin(th + dir * M_PI_2);
	}
	else
		return (-1);
	return (0);
}

int		player_move(t_game *g, int key)
{
	double	dx;
	double	dy;
	double	nx;
	double	ny;
	int		chk;

	dx = 0;
	dy = 0;
	if (move_offset(g->th, key, &dx, &dy) < 0)
		return (ft_strerror(-19));
	nx = g->px + dx;
	ny = g->py + dy;
	chk = map_get_cell(g, (int)nx, (int)ny);
	if (chk != 0 && !user_dir(chk))
		return (-1);
	g->px = nx;
	g->py = ny;
	return (0);
}

void	player_rotate(t_game *g, double th)
{
	g->th += th;
	if (g->th < 0)
		g->th += (M_PI * 2);
	else if (g->th > (M_PI * 2))
		g->th -= (M_PI * 2);
}
