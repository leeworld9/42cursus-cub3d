/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_button_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 02:39:37 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/15 02:43:44 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		button_press(int button, int x, int y, t_game *g)
{
	int dir;

	if (button == 1 || button == 3)
	{
		if (button == 1)
			dir = 1;
		if (button == 3)
			dir = -1;
		player_rotate(g, ROTATE_UNIT * dir);
		if (render(g) < 0)
			return (-1);
	}
	else
	{
		printf("Error : Invaild Mouse Button ");
		printf("> Button %d at %dx%d.\n", button, x, y);
	}
	return (0);
}
