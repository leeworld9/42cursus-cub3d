/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:37:48 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/15 02:41:52 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		get_tx(t_game *g)
{
	double	txratio;

	if (g->wall.wdir == DIR_W || g->wall.wdir == DIR_E)
		txratio = g->wall.wy - floor(g->wall.wy);
	else
		txratio = g->wall.wx - floor(g->wall.wx);
	return ((int)(txratio * 64));
}

int		render(t_game *g)
{
	double	zbuf[g->win.x];
	int		**visible;
	int		x;
	double	wdist;

	if ((visible = malloc_2d(g->map.mx, g->map.my)) == NULL)
		return (ft_strerror(-11));
	memset_2d(visible, g->map.mx, g->map.my, 0);
	ft_memset(zbuf, 0, sizeof(double) * g->win.x);
	x = 0;
	while (x < g->win.x)
	{
		wdist = cast_single_ray(x, g, visible);
		zbuf[x] = wdist;
		draw_wall(g, wdist, x, get_tx(g));
		draw_floor_ceiling(g, wdist, x);
		x++;
	}
	draw_sprites(g, visible, zbuf);
	draw_map(g);
	return (free_2d_i(visible, g->map.mx, 0));
}

int		draw_loop(t_game *g)
{
	mlx_put_image_to_window(g->mlx, g->win.w, g->img.i, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_game	g;
	int		chk;

	cub_init(&g);
	chk = param_check(&g, argc, argv);
	if (chk == 2)
	{
		cub_set(&g);
		g.win.w = mlx_new_window(g.mlx, g.win.x, g.win.y, "cub3D");
		if (render(&g) < 0)
			return (-1);
		mlx_hook(g.win.w, KEY_PRESS_EVNT, 1L << 0, key_press, &g);
		mlx_hook(g.win.w, BUTTON_PRESS_EVNT, 1L << 2, button_press, &g);
		mlx_hook(g.win.w, EXIT_EVNT, 1L << 17, event_exit, &g);
		mlx_loop_hook(g.mlx, draw_loop, &g);
		mlx_loop(g.mlx);
	}
	else if (chk == 3)
	{
		cub_set(&g);
		get_bitmap(&g, 1);
	}
	else
		exit(0);
	return (0);
}
