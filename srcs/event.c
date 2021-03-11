/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:45 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/12 01:31:42 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_game *game)
{
	if (key < 0 || key == KEY_ESC) 
		exit(0);
	if(key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
	{
		if (player_move(game, key, MOVE_UNIT) == 0 )
			render(game);
	}
	if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		player_rotate(game, ROTATE_UNIT * (key == KEY_LEFT ? 1 : -1));
		render(game);
	}
	return (0);
}

int		button_exit(int button, t_game *game)
{
    printf("button : %d\n", button);
	mlx_destroy_display(game->mlx);
	exit(0);
	return (0);
}

int get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
	if (key == KEY_W || key == KEY_S)
	{
		*pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
		*pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
	}
	else if (key == KEY_A || key == KEY_D)
	{
		*pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
	 	*pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
	}
	else
		return (-1); // 에러처리 필요?
	return (0);
}

int player_move( t_game *game, int key, double amt )
{
	double	dx;
	double	dy;
	double	nx;
	double	ny;
	int		chk;

	dx = 0;
	dy = 0;
	if( get_move_offset(game->th, key, amt, &dx, &dy) < 0 )
	{
		//error 출력하도록 다른 함수 사용, subject 확인
		fprintf(stderr,"player_move: invalid key %d\n", key);
		return (-1);
	}
	nx = game->px + dx;
	ny = game->py + dy;
	chk = map_get_cell(game, (int)nx, (int)ny);
	if(chk != 0 && !user_dir(chk))
	{
		//printf("nx : %f, ny : %f\n", nx, ny);
		//printf("chk : %d", chk);
		printf("** bump !\n");
		//여기도 에러처리 필요
		return (-1);
	}
	game->px = nx;
	game->py = ny;
	return (0);
}

void player_rotate(t_game *game, double th)
{
	game->th += th;
	if (game->th < 0)
		game->th += (M_PI * 2);
	else if(game->th > (M_PI * 2))
		game->th -= (M_PI * 2);
}
