/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 07:22:28 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/14 11:39:06 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	user_dir(int c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (true);
	else
		return (false);
}

int		user_deg(int c)
{
	if (c == 'N')
		return (180);
	else if (c == 'E')
		return (90);
	else if (c == 'W')
		return (270);
	else
		return (0);
}

int		user_errchk(int chk)
{
	if (chk == 1)
		return (0);
	else if (chk > 1)
		return (ft_strerror(-16));
	else
		return (ft_strerror(-17));
}

int		user_location(t_game *g)
{
	int x;
	int y;
	int chk;

	chk = 0;
	x = 0;
	while (x < g->map.mx)
	{
		y = 0;
		while (y < g->map.my)
		{
			if (user_dir(map_get_cell(g, x, y)))
			{
				g->px = x + 0.5;
				g->py = y + 0.5;
				g->th = deg2rad(user_deg(map_get_cell(g, x, y)));
				chk++;
			}
			y++;
		}
		x++;
	}
	return (user_errchk(chk));
}
