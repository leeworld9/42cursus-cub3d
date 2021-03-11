
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:51 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/10 07:48:06 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render(t_game *game)
{
	t_wall wall;
	double zbuf[game->win.winx]; /* distances to the wall slices */

	int **visible = malloc(sizeof(int *) * game->map.mx);
	for (int i = 0; i < game->map.mx; i++)
		visible[i] = malloc(sizeof(int) * game->map.my);

	//초기화
	for (int i = 0; i < game->map.mx; i++)
	{
		for (int j = 0; j < game->map.my; j++)
			visible[i][j] = 0;
	}
	
	for( int x=0; x<game->win.winx; x++ ) {
		double wdist = cast_single_ray(x, game, &wall, visible);
		zbuf[x] = wdist;
		
		double txratio = (wall.wdir == DIR_W || wall.wdir == DIR_E) ? (wall.wy-floor(wall.wy)) : (wall.wx-floor(wall.wx));
		int tx = (int)(txratio * game->wall_n.width);
		//tx는 뭘의 미하지?
		//printf("tx : %d, wy-floor(wy) : %f, wx-floor(wx) : %f\n", tx, wall.wy-floor(wall.wy), wall.wx-floor(wall.wx));
		draw_wall(game, wdist, x, &wall, tx);
	}
	//sprite 위에 함수에 넣으면 코드 많이 줄지 않을까?
	draw_sprites(game, visible, zbuf);

	//수정필요
	//draw_map(game);

	//free
	for (int i = 0; i < game->map.mx; i++)
		free(visible[i]);
	free(visible);
}


int		draw_loop(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win.win, game->img.img, 0, 0);
	return (0);
}

void cub_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win.winx = 0;
	game->win.winy = 0;
	game->img.data = NULL;
	game->top.color = 0x000000;
	game->bottom.color = 0x000000;
	game->wall_n.data = NULL;
	game->wall_e.data = NULL;
	game->wall_w.data = NULL;
	game->wall_s.data = NULL;
	game->sprite.data = NULL;
	game->map.map = NULL;
	game->map.chk = 0;
	game->map.mx = 0;
	game->map.my = 0;
	game->px = 0;
	game->py = 0;
	game->th = 0;
}

void cub_set(t_game *game)
{
	game->win.win = mlx_new_window(game->mlx, game->win.winx, game->win.winy, "cub3D");
	game->img.img = mlx_new_image(game->mlx, game->win.winx, game->win.winy);
	game->img.data = (unsigned int*)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_size, &game->img.endian);
	game->fov_v = deg2rad(FOV) * (double)game->win.winy / (double)game->win.winx;
	game->pixel_per_angle = (game->win.winx - 1.0) / deg2rad(FOV);
	game->angle_per_pixel = deg2rad(FOV) / (game->win.winx - 1.0);
}

int main(int argc, char **argv)
{
	t_game	game;
	int chk;

	//초기값
	cub_init(&game);

	chk = param_chk(&game, argc, argv);
	//printf("chk : %d\n", chk);
	if (chk == 2)
	{
		//printf("mx : %d, my : %d\n", game.map.mx, game.map.my);
		cub_set(&game);
		render(&game);


		mlx_hook(game.win.win, KEY_PRESS_EVNT, 1L>>0, key_press, &game);
		mlx_hook(game.win.win, EXIT_EVNT, 1L << 17, button_exit, &game);
		mlx_loop_hook(game.mlx, draw_loop, &game);
	
		mlx_loop(game.mlx);
	}
	else if (chk == 3)
	{
		cub_set(&game);
		render(&game);
		get_bitmap(&game, 1); // 하고 디스트로이 free()필요
	}

	else
		return (-1); // error
	return (0);
}