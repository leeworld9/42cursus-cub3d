/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:36 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/12 01:33:34 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int cmp_sprites(const void* a, const void* b)
{
	if (((const t_sprite*)a)->dist > ((const t_sprite*)b)->dist)
		return (-1);
	else
		return (1);
}

t_sprite* get_visible_sprites(t_game *game, int **vis, int* cnt)
{
	int n = 0;
	t_sprite* sp = NULL;

	for( int x=0; x<game->map.mx; x++ ) {
		for( int y=0; y<game->map.my; y++ ) {
			if( vis[x][y] == 0 || map_get_cell(game, x, y) <= 1 || user_dir(map_get_cell(game, x, y))) // e뒤에는 NEWS를 위해서 임시로
				continue;
			if( n == 0 ) // need free()
				sp = (t_sprite*)malloc(sizeof(t_sprite));
			else 
				sp = (t_sprite*)realloc(sp, sizeof(t_sprite)*(n+1));

			//sp[n].tex = (map_get_cell(x,y) - 1) + 2; //스프라이트 여러개라고 가정했을때 몇번째 인지. (여기선 기본적으로 5이상으로 설정되어 있는듯)
			sp[n].sx = x;
			sp[n].sy = y;
			sp[n].th = atan2((y+0.5)-(game->py), (x+0.5)-(game->px));
			if( sp[n].th < 0 )
				sp[n].th += (M_PI * 2);  //?
			sp[n].dist = l2dist(game->px, game->py, x+0.5, y+0.5) * cos(game->th - sp[n].th);
			n++;
		}
	}
	*cnt = n;
	return (sp);
}

void draw_sprites(t_game *game, int **vis, double zbuf[])
{
	int nsp = 0;
	t_sprite *sp = get_visible_sprites(game, vis, &nsp);

	//퀵정렬 못씀 따로 메소드 만들기.
	qsort(sp, nsp, sizeof(t_sprite), cmp_sprites);  /* order by dist DESC */

	for( int i=0; i<nsp; i++ ) {
		int sh = get_wall_height(game, sp[i].dist); /* sprite height (=width) */
		double lum = get_luminosity(game, sp[i].dist);

		double angle = sp[i].th - game->th; /* angle of sprite relative to FOV center */
		if(angle > M_PI) 
			angle -= (M_PI * 2);   /* ensures -pi < angle < +pi */
		else if( angle < -M_PI ) 
			angle += (M_PI * 2);

		//설명 가능해야함!!
		int cx = (int)((deg2rad(FOV) / 2.0 - angle) * game->pixel_per_angle); /* screen pos of sprite, in pixels */
		int xmin = max(0, cx - sh/2); /* clipping */
		int xmax = min(game->win.winx, cx + sh/2);

		for( int x=xmin; x<xmax; x++ ) {
			if( sp[i].dist > zbuf[x] ) 
				continue; /* behind wall */
			//if( sp[i].dist < PL_RADIUS ) 
			//	continue; /* too close */

			double txratio = (double)(x-cx)/sh + 0.5;
			int tx = (int)(txratio * game->sprite.width); /* texture col # */
			int y0 = (int)((game->win.winy - sh)/2.0);

			for( int y=max(0, y0); y<min(game->win.winy, y0+sh); y++ ) {
				int ty = (int)((double)(y-y0) * game->sprite.height / sh); /* texture row # */
				int color = game->sprite.data[game->sprite.width * ty + tx];
				//printf("color : %d\n", color);
				if(color == 0x000000) 
					continue; /* black == transparent */
				game->img.data[game->win.winx * y + x] = fade_color(game->sprite.data[game->sprite.width * ty + tx], lum);
			}
		}
	}
	if( nsp > 0 )
		free(sp);
}
