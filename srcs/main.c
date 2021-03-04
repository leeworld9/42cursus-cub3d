#include "cub3d.h"

#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))

#define  SX         800     /* screen width */
#define  SY         600     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0

#define  MAPX   11
#define  MAPY   15

#define  _2PI       6.28318530717958647692  /* 2 * M_PI */

#define  ROT_UNIT   0.03    /* rad */
#define  MOVE_UNIT  0.1

# define KEY_EVENT_PRESS    2

static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;

typedef struct  s_img
{
    void        *img;
    int         *data;
    int            width;
    int            height;
    int         bpp;
    int         line_size;
    int         endian;
}                t_img;

typedef struct s_sprite
{
    int tex;     /* texture bitmap no. */
    int x, y;    /* position in the map */
    double dist; /* distance from the player */
    double th;   /* angle */
}              t_sprite;

typedef struct    s_game
{
    void        *mlx;
    void        *win;
    int            map[MAPX][MAPY];
    t_img        img;
    t_img       wall_e; 
    t_img       wall_w; 
    t_img       wall_s; 
    t_img       wall_n; 
    t_img       bottom;
    t_img       top;
    t_img       sprite;
	double px;
	double py;
	double th;
}               t_game;

enum { VERT, HORIZ };

typedef enum 
{
    DIR_N = 0,
    DIR_E,
    DIR_W,
    DIR_S
}       dir_t;


static int map[MAPX][MAPY] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

int map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

int sgn( double d )
{
    return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx*dx + dy*dy);
}

// 다시보기
bool get_wall_intersection( double ray, double px, double py, dir_t *wdir, double* wx, double* wy, int **vis)
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    // printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
    //     rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

    double f=INFINITY, g=INFINITY;
    bool hit = false;
    int hit_side; /* either VERT or HORIZ */

    while( !hit )
    {
        int mapx, mapy;

        if( xstep != 0 ) f = xslope * (nx-px) + py;
        if( ystep != 0 ) g = yslope * (ny-py) + px;

        /* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
        double dist_v = l2dist(px, py, nx, f);
        double dist_h = l2dist(px, py, g, ny);

        if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
            mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
            mapy = (int) f;
            hit_side = VERT;
            //printf(" V(%d, %.2f) ->", mapx, f);
        }
        else {  /* HORIZ is nearer; go along y-axis */
            mapx = (int) g;
            mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
            hit_side = HORIZ;
            //printf(" H(%.2f, %d) ->", g, mapy);
        }
        int cell = map_get_cell(mapx, mapy);
        if( cell < 0 ) break;   /* out of map */

        if( cell == 1 ) {   /* hit wall? */
            if( hit_side == VERT ) {
                *wdir = (xstep > 0) ? DIR_W : DIR_E;
                *wx = nx;
                *wy = f;
				//printf("wdir_V : %d\n", *wdir);
            }
            else { /* HORIZ */
                *wdir = (ystep > 0) ? DIR_S : DIR_N;
                *wx = g;
                *wy = ny;
				//printf("wdir_h : %d\n", *wdir);
            }
            hit = true;
			//printf("wdir : %d\n", *wdir);
            //printf(" hit wall!\n");
            break;
        }
        vis[mapx][mapy] = 1;  /* 이 행을 추가 ! */

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

double cast_single_ray( int x, double px, double py, double th, dir_t* wdir, double* wx, double* wy, int **vis)
{
    double ray = (th + FOVH_2) - (x * ANGLE_PER_PIXEL);

    //dir_t wdir;     /* direction of wall */
    //double wx, wy;  /* coord. of wall intersection point */

    if( get_wall_intersection(ray, px, py, wdir, wx, wy, vis) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(px, py, *wx, *wy);
    wdist *= cos(th - ray);  /* 보정 */

    return wdist;
}

int get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}

void draw_wall( t_game *game, double wdist, int x, int color, dir_t wdir, double wx, double wy, int tx)
{
    int wh = get_wall_height(wdist);    /* wall height, in pixels */

    /* starting/ending y pos of the wall slice */
    int y0 = (int)((SY - wh)/2.0);
    int y1 = y0 + wh - 1;

    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(SY-1, y1);

    if( y1 < SY-1 ) {
        for( int y=y1+1; y<SY; y++ ) {
            double h = (double)(SY-1-y)/SY;
            // WALL_H은 1로 설정되어 있음
            double D = (WALL_H / (2.0 * tan(FOV_V/2))) / (1.0 - 2*h);

            double d_ratio = D / wdist;
            double fx = game->px + (wx - game->px) * d_ratio; /* floor coord. */
            double fy = game->py + (wy - game->py) * d_ratio;

             /* floor */
            int tx = (int)((fx-floor(fx)) * game->top.width); /* texture col # */
            int ty = (int)((fy-floor(fy)) * game->top.height); /* texture row # */
            game->img.data[SX * (SY-1-y) + x] = game->top.data[game->top.width * ty + tx];

            /* ceiling */
            tx = (int)((fx-floor(fx)) * game->bottom.width); /* texture col # */
            ty = (int)((fy-floor(fy)) * game->bottom.height); /* texture row # */
            game->img.data[SX * y + x] = game->bottom.data[game->top.width * ty + tx];
        }
    }

	for( int y=ystart; y<=yend; y++ )
    {
        //멀어지면 텍스쳐도 작아저야하는데...? 좀이해가 안감 앞에 다시 보자
        if(wdir == DIR_E)
        {
            int ty = (int)((double)(y-y0) * game->wall_e.height / wh);
            game->img.data[SX * y + x] = game->wall_e.data[game->wall_e.width * ty + tx];
        }
        else if(wdir == DIR_W)
        {
            int ty = (int)((double)(y-y0) * game->wall_w.height / wh);
            game->img.data[SX * y + x] = game->wall_w.data[game->wall_w.width * ty + tx];
        }
        else if(wdir == DIR_N)
        {
            int ty = (int)((double)(y-y0) * game->wall_n.height / wh);
            game->img.data[SX * y + x] = game->wall_n.data[game->wall_n.width * ty + tx];
        }
        else if(wdir == DIR_S)
        {
            int ty = (int)((double)(y-y0) * game->wall_s.height / wh);
            game->img.data[SX * y + x] = game->wall_s.data[game->wall_s.width * ty + tx];
        }     
    }

}

void player_rotate(t_game *game, double th )
{
    game->th += th;
    if( game->th < 0 ) game->th += _2PI;
    else if( game->th > _2PI ) game->th -= _2PI;
}

static void	clear_win(t_game *game)
{
	for(int x=0; x<SX; x++)
	{
		for(int y=0; y<SY; y++)
		{
			game->img.data[SX * y + x] = 0x000000;
		}
	}
}


/////////////////////스프라이트//////////////////////////////////
static int cmp_sprites( const void* a, const void* b )
{
    return (((const t_sprite*)a)->dist > ((const t_sprite*)b)->dist) ? -1 : 1;
}

static t_sprite* get_visible_sprites(t_game *game, int **vis, int* pcnt)
{
    int n = 0;
    t_sprite* sp = NULL; /* dynamic array */

    /* build list of visible sprites */
    for( int x=0; x<MAPX; x++ ) {
        for( int y=0; y<MAPY; y++ ) {
            if( vis[x][y] == 0 || map_get_cell(x,y) <= 1 )
                continue;

            if( n == 0 )
                sp = (t_sprite*) malloc(sizeof(t_sprite));
            else 
                sp = (t_sprite*) realloc(sp, sizeof(t_sprite)*(n+1));

            //sp[n].tex = (map_get_cell(x,y) - 1) + 2; //스프라이트 여러개라고 가정했을때 몇번째 인지. (여기선 기본적으로 5이상으로 설정되어 있는듯)
            sp[n].x = x;
            sp[n].y = y;
            sp[n].th = atan2((y+0.5)-(game->py), (x+0.5)-(game->px));
            if( sp[n].th < 0 )
                sp[n].th += _2PI;  //?
            sp[n].dist = l2dist(game->px, game->py, x+0.5, y+0.5) * cos(game->th - sp[n].th);
            n++;
        }
    }
    *pcnt = n;
    return sp;
}

static const double PIXEL_PER_ANGLE = (SX-1.) / FOV_H;



static void draw_sprites(t_game *game, int **vis, double zbuf[SX])
{
    int nsp = 0;
    t_sprite* sp = get_visible_sprites(game, vis, &nsp);

    qsort(sp, nsp, sizeof(t_sprite), cmp_sprites);  /* order by dist DESC */

    for( int i=0; i<nsp; i++ ) {
        int sh = get_wall_height(sp[i].dist); /* sprite height (=width) */
        //img_t* ptex = texture_get(sp[i].tex);
        t_img ptex;
        ptex.img = mlx_xpm_file_to_image(game->mlx, "./imgs/sprite.xpm", &ptex.width, &ptex.height);
        ptex.data = (int *)mlx_get_data_addr(ptex.img, &ptex.bpp, &ptex.line_size, &ptex.endian);

        double angle = sp[i].th - game->th; /* angle of sprite relative to FOV center */
        if( angle > M_PI ) 
            angle -= _2PI;   /* ensures -pi < angle < +pi */
        else if( angle < -M_PI ) 
            angle += _2PI;

        int cx = (int)((FOVH_2 - angle) * PIXEL_PER_ANGLE); /* screen pos of sprite, in pixels */
        int xmin = max(0, cx - sh/2); /* clipping */
        int xmax = min(SX, cx + sh/2);

        for( int x=xmin; x<xmax; x++ ) {
            if( sp[i].dist > zbuf[x] ) continue; /* behind wall */
            //if( sp[i].dist < PL_RADIUS ) continue; /* too close */
            if( sp[i].dist < 0.2 ) continue; /* too close */
            /////////////////////?????????????

            double txratio = (double)(x-cx)/sh + 0.5;
            int tx = (int)(txratio * ptex.width); /* texture col # */
            int y0 = (int)((SY - sh)/2.0);

            for( int y=max(0, y0); y<min(SY, y0+sh); y++ ) {
                int ty = (int)((double)(y-y0) * ptex.height / sh); /* texture row # */
                int color = ptex.data[ptex.width * ty + tx];
                if(color == 0xffffff) 
                    continue; /* black == transparent */
                game->img.data[SX * y + x] = ptex.data[ptex.width * ty + tx];
            }
        }
    }
    if( nsp > 0 ) free(sp);
}

//////////////////////////////////////////////////////////////////////////////// 

void render(t_game *game)
{
    static int wall_colors[] = {    /* DIR_N, E, W, S */
        0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
    };

	clear_win(game);
    double wx, wy;
    double zbuf[SX]; /* distances to the wall slices */

    int **visible = malloc(sizeof(int *) * MAPX);
    for (int i = 0; i < MAPX; i++)
        visible[i] = malloc(sizeof(int) * MAPY);

    //초기화
    for (int i = 0; i < MAPX; i++)
    {
        for (int j = 0; j < MAPY; j++)
            visible[i][j] = 0;
    }
	
    for( int x=0; x<SX; x++ ) {
        dir_t wdir;
        double wdist = cast_single_ray(x, game->px, game->py, game->th, &wdir, &wx, &wy, visible);
        zbuf[x] = wdist;
        
        double txratio = (wdir == DIR_W || wdir == DIR_E) ? (wy-floor(wy)) : (wx-floor(wx));
        int tx = (int)(txratio * game->wall_n.width);

        //printf("tx : %d, wy-floor(wy) : %f, wx-floor(wx) : %f\n", tx, wy-floor(wy), wx-floor(wx));
		draw_wall(game, wdist, x, wall_colors[wdir], wdir, wx, wy, tx);
    }
    //temp
    // for (int i = 0; i < MAPX; i++)
    // {
    //     for (int j = 0; j < MAPY; j++)
    //         printf("%d ",visible[i][j]);
    //         //printf("visible[%d][%d] : %d\n", i, j, visible[i][j]);
    //     printf("\n");
    // }
    draw_sprites(game, visible, zbuf);

    //free
    for (int i = 0; i < MAPX; i++)
        free(visible[i]);
    free(visible);
}

//다시보기 정확히
static int get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
        default: /* invalid */
            return -1;
    }
    return 0;
}

int player_move( t_game *game, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

    if( get_move_offset(game->th, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"player_move: invalid key %d\n", key);
        return -1;
    }
    nx = game->px + dx;
    ny = game->py + dy;

    if( map_get_cell((int)nx, (int)ny) != 0 ) {
        printf("** bump !\n");
        return -1;
    }
    game->px = nx;
    game->py = ny;
    return 0;
}

// w,a 와 같이 눌렸을때 처리도 필요
int        key_press(int keycode, t_game *game)
{
	if( keycode < 0 || keycode == KEY_ESC ) 
		exit(0);
    if( keycode == KEY_LEFT || keycode == KEY_RIGHT )
	{
		player_rotate(game, ROT_UNIT * (keycode==KEY_LEFT ? 1 : -1));
		render(game);
	}
	else if( keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D ) {
		if( player_move(game, keycode, MOVE_UNIT) == 0 )
			render(game);
    }
	
    return (0);
}


int        draw_loop(t_game *game)
{


    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    return (0);
}

int main( int ac, char** av )
{
    if( ac != 4 ) {
        fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
        exit(1);
    }
    t_game	game;
	game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SX, SY, "cub3D");

    double px, py, th;
    game.px = atof(av[1]);
    game.py = atof(av[2]);
    game.th = deg2rad(atof(av[3]));
    game.img.img = mlx_new_image(game.mlx, SX, SY);
    game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_size, &game.img.endian);

    
    game.wall_e.img = mlx_xpm_file_to_image(game.mlx, "./imgs/stone_texture_e.xpm", &game.wall_e.width, &game.wall_e.height);
    game.wall_e.data = (int *)mlx_get_data_addr(game.wall_e.img, &game.wall_n.bpp, &game.wall_e.line_size, &game.wall_e.endian);

    game.wall_w.img = mlx_xpm_file_to_image(game.mlx, "./imgs/stone_texture_w.xpm", &game.wall_w.width, &game.wall_w.height);
    game.wall_w.data = (int *)mlx_get_data_addr(game.wall_w.img, &game.wall_w.bpp, &game.wall_w.line_size, &game.wall_w.endian);

    game.wall_s.img = mlx_xpm_file_to_image(game.mlx, "./imgs/stone_texture_s.xpm", &game.wall_s.width, &game.wall_s.height);
    game.wall_s.data = (int *)mlx_get_data_addr(game.wall_s.img, &game.wall_s.bpp, &game.wall_s.line_size, &game.wall_s.endian);

    game.wall_n.img = mlx_xpm_file_to_image(game.mlx, "./imgs/stone_texture_n.xpm", &game.wall_n.width, &game.wall_n.height);
    game.wall_n.data = (int *)mlx_get_data_addr(game.wall_n.img, &game.wall_n.bpp, &game.wall_n.line_size, &game.wall_n.endian);

    game.top.img = mlx_xpm_file_to_image(game.mlx, "./imgs/top.xpm", &game.top.width, &game.top.height);
    game.top.data = (int *)mlx_get_data_addr(game.top.img, &game.top.bpp, &game.top.line_size, &game.top.endian);
    game.bottom.img = mlx_xpm_file_to_image(game.mlx, "./imgs/bottom.xpm", &game.bottom.width, &game.bottom.height);
    game.bottom.data = (int *)mlx_get_data_addr(game.bottom.img, &game.bottom.bpp, &game.bottom.line_size, &game.bottom.endian);

    // t_img sp[3];

    // sp[0].img = mlx_xpm_file_to_image(game.mlx, "./imgs/sprite.xpm", &sp[0].width, &sp[0].height);
    // sp[0].data = (int *)mlx_get_data_addr(sp[0].img, &sp[0].bpp, &sp[0].line_size, &sp[0].endian);
    // sp[1].img = mlx_xpm_file_to_image(game.mlx, "./imgs/sprite.xpm", &sp[1].width, &sp[1].height);
    // sp[1].data = (int *)mlx_get_data_addr(sp[1].img, &sp[1].bpp, &sp[1].line_size, &sp[1].endian);
    // sp[2].img = mlx_xpm_file_to_image(game.mlx, "./imgs/sprite.xpm", &sp[2].width, &sp[2].height);
    // sp[2].data = (int *)mlx_get_data_addr(sp[2].img, &sp[2].bpp, &sp[2].line_size, &sp[2].endian);





    // game.sprite.img = mlx_xpm_file_to_image(game.mlx, "./imgs/sprite.xpm", &game.sprite.width, &game.sprite.height);
    // game.sprite.data = (int *)mlx_get_data_addr(game.sprite.img, &game.sprite.bpp, &game.sprite.line_size, &game.sprite.endian);


	render(&game);
	mlx_hook(game.win, KEY_EVENT_PRESS, 1L>>0, key_press, &game);
    mlx_loop_hook(game.mlx, draw_loop, &game);
 
    mlx_loop(game.mlx);
    return (0);
}