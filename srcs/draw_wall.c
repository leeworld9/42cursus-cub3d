/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 03:34:40 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/12 01:32:19 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_wall_height(t_game *game, double dist)
{
	double view_h;

	view_h = 2.0 * dist * tan(game->fov_v/2.0);
	return ((int)(game->win.winy * (WALL_H / view_h)));
}

int map_get_cell(t_game *game, int x, int y)
{
	char c;
	if (x >= 0 && x < game->map.mx && y >= 0 && y < game->map.my)
	{	
		c = game->map.map[x][y];
		if (ft_isdigit(c))
			return (c - '0');
		else
			return (c);
	}
	else
		return (-1);
}

void draw_wall(t_game *game, double wdist, int x, t_wall *wall, int tx)
{
	int wh;	/* wall height, in pixels */
	int y0;
	int y1;
	int ystart;
	int yend;

	wh = get_wall_height(game, wdist);
	y0 = (int)((game->win.winy - wh)/2.0);
	y1 = y0 + wh - 1;
	ystart = max(0, y0);
	yend = min(game->win.winy - 1, y1);
	
	if(y1 < game->win.winy - 1) {
		for(int y = y1 + 1; y < game->win.winy; y++) {
			double h = (double)(game->win.winy - 1 - y) / game->win.winy;
			// WALL_H은 1로 설정되어 있음
			double D = (WALL_H / (2.0 * tan(game->fov_v/2))) / (1.0 - 2*h);
			double lum_f = get_luminosity(game, D);
			//double d_ratio = D / wdist;
			//double fx = game->px + (wall->wx - game->px) * d_ratio; /* floor coord. */
			//double fy = game->py + (wall->wy - game->py) * d_ratio;
			

			//보너스에 바닥 텍스처 있음, 기본은 칼라
			 /* floor */
			//int tx = (int)((fx-floor(fx)) * game->top.width); /* texture col # */
			//int ty = (int)((fy-floor(fy)) * game->top.height); /* texture row # */
			//game->img.data[game->win.winx * (game->win.winy-1-y) + x] = fade_color(game->top.data[game->top.width * ty + tx] , lum_f);
			game->img.data[game->win.winx * (game->win.winy-1-y) + x] = fade_color(game->top.color , lum_f);

			/* ceiling */
			//tx = (int)((fx-floor(fx)) * game->bottom.width); /* texture col # */
			//ty = (int)((fy-floor(fy)) * game->bottom.height); /* texture row # */
			//game->img.data[game->win.winx * y + x] = fade_color(game->bottom.data[game->bottom.width * ty + tx] , lum_f);
			game->img.data[game->win.winx * y + x] = fade_color(game->bottom.color , lum_f);
		}
	}
	
	for( int y=ystart; y<=yend; y++ )
	{
		double lum = get_luminosity(game, wdist); /* 0과 1 사이 */
		
		if(wall->wdir == DIR_E)
		{
			int ty = (int)((double)(y-y0) * game->wall_e.height / wh);
			game->img.data[game->win.winx * y + x] = fade_color(game->wall_e.data[game->wall_e.width * ty + tx] , lum);
		}
		else if(wall->wdir == DIR_W)
		{
			int ty = (int)((double)(y-y0) * game->wall_w.height / wh);
			game->img.data[game->win.winx * y + x] = fade_color(game->wall_w.data[game->wall_w.width * ty + tx] , lum);
		}
		else if(wall->wdir == DIR_N)
		{
			int ty = (int)((double)(y-y0) * game->wall_n.height / wh);
			game->img.data[game->win.winx * y + x] = fade_color(game->wall_n.data[game->wall_n.width * ty + tx] , lum);
		}
		else if(wall->wdir == DIR_S)
		{
			int ty = (int)((double)(y-y0) * game->wall_s.height / wh);
			game->img.data[game->win.winx * y + x] = fade_color(game->wall_s.data[game->wall_s.width * ty + tx] , lum);
		}
		
	}

}

bool get_wall_intersection(double ray, t_game *game, t_wall *wall, int **vis)
{
	int xstep = sign(cos(ray));  /* +1 (right), 0 (no change), -1 (left) */
	int ystep = sign(sin(ray));  /* +1 (up),	0 (no change), -1 (down) */

	double xslope = (xstep == 0) ? INFINITY : tan(ray);
	double yslope = (ystep == 0) ? INFINITY : 1.0/tan(ray);

	double nx = (xstep > 0) ? floor(game->px)+1 : ((xstep < 0) ? ceil(game->px)-1 : game->px);
	double ny = (ystep > 0) ? floor(game->py)+1 : ((ystep < 0) ? ceil(game->py)-1 : game->py);

	double f=INFINITY, g=INFINITY;
	bool hit = false;
	t_hitside hs; /* either VERT or HORIZ */

	while( !hit )
	{
		int mapx, mapy;

		if( xstep != 0 )
			f = xslope * (nx-game->px) + game->py;
		if( ystep != 0 )
			g = yslope * (ny-game->py) + game->px;

		/* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
		double dist_v = l2dist(game->px, game->py, nx, f);
		double dist_h = l2dist(game->px, game->py, g, ny);

		if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
			mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
			mapy = (int) f;
			hs = VERT;
			//printf(" V(%d, %.2f) ->", mapx, f);
		}
		else {  /* HORIZ is nearer; go along y-axis */
			mapx = (int) g;
			mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
			hs = HORIZ;
			//printf(" H(%.2f, %d) ->", g, mapy);
		}
		int cell = map_get_cell(game, mapx, mapy);
		if( cell < 0 ) break;   /* out of map */

		if( cell == 1 ) {   /* hit wall? */
			if( hs == VERT ) {
				wall->wdir = (xstep > 0) ? DIR_W : DIR_E;
				wall->wx = nx;
				wall->wy = f;
				//printf("wall->wdir_V : %d\n", *wall->wdir);
			}
			else { /* HORIZ */
				wall->wdir = (ystep > 0) ? DIR_S : DIR_N;
				wall->wx = g;
				wall->wy = ny;
				//printf("wall->wdir_h : %d\n", *wall->wdir);
			}
			hit = true;
			//printf("wall->wdir : %d\n", *wall->wdir);
			//printf(" hit wall!\n");
			break;
		}
		vis[mapx][mapy] = 1;  /* 이 행을 추가 ! */

		if( hs == VERT ) nx += xstep;
		else ny += ystep;
	}
	/* end of while(!hit) */

	return hit;
}
