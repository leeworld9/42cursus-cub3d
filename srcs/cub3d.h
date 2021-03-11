/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:48:13 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/12 01:35:40 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

//gnl//
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
//////

# define BYTES_PER_PIXEL	4
# define FILE_HEADER_SIZE	14
# define INFO_HEADER_SIZE	40

# define KEY_ESC			65307
# define KEY_W				119
# define KEY_S				115
# define KEY_A				97
# define KEY_D				100
# define KEY_UP				65362
# define KEY_DOWN			65364
# define KEY_LEFT			65361
# define KEY_RIGHT			65363

# define	EPS			(1e-06)
// # define	is_zero(d)	(fabs(d) < EPS)
// # define	deg2rad(d)	((d)*M_PI/180.0)	/* degree to radian */
// # define	rad2deg(d)	((d)*180.0/M_PI)	/* radian to degree */
// #define  min(a,b)       ((a)<(b)? (a):(b))
// #define  max(a,b)       ((a)>(b)? (a):(b))


//해상도 변경시에는 make re를 안하면 적용안됨, make는 안먹힘.... 의존성 체크 안되나?
//링킹과정 확인하기, 정확히는 h가 사용되는 시기 파악, o 만들때는 안쓰이지 않나? 모르겠다 확인 필요
// # define	SX				800	 /* screen width */
// # define	SY				600	 /* screen height */
# define	FOV				60	  /* field of view (in degree) */ //시야각


# define 	WALL_H			1.0

# define 	MAPX			11
# define	MAPY			15

# define	ROTATE_UNIT		0.03	/* rad */
# define	MOVE_UNIT		0.1

# define	TILE_SIZE		10
# define	USER_SIZE		2
# define	USER_PAD		30

# define	KEY_PRESS_EVNT	2
# define 	EXIT_EVNT		33
# define 	BTN_PRESS_EVNT	4

typedef struct  s_img
{
	void	*img;
	unsigned int *data;
	int		width;
	int		height;
	int		bpp;
	int		line_size;
	int		endian;
	unsigned int	color;
}	t_img;

typedef struct s_sprite
{
	//int	tex;	 /* texture bitmap no. */
	int	sx;
	int	sy;
	double	dist;
	double	th;
}			  t_sprite;

typedef enum e_dir
{
	DIR_N = 0,
	DIR_E,
	DIR_W,
	DIR_S
}			t_dir;

typedef struct s_wall
{
	double	wx;
	double	wy;
	t_dir	wdir;
}			t_wall;

typedef struct s_win
{
	void	*win;
	int		winx;
	int		winy;
}			t_win;

typedef struct	s_map
{
	char	**map;
	int		mx; //tmp
	int		my; //tmp
	int		chk;
}				t_map;

typedef struct	s_game
{
	void	*mlx;
	t_win	win;
	t_map	map;
	double	fov_v;
	double	pixel_per_angle;
	double	angle_per_pixel;
	t_img	img;
	t_img	bottom;
	t_img	top;
	t_img	sprite;
	t_img	mapimg;
	t_img	wall_n;
	t_img	wall_s;
	t_img	wall_w;
	t_img	wall_e;
	double	px;
	double	py;
	double	th;
}			   t_game;


typedef enum e_hitside
{
	VERT,
	HORIZ
}			t_hitside;

// static int map[MAPX][MAPY] = {
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 'W', 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1},
// 	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
// 	{1, 1, 1, 1, 0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
// 	{1, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// 	};

void	draw_square(t_game *game, int x, int y, int color);
void	draw_squares(t_game *game);
void	draw_line(t_game *game, double x1, double y1, double x2, double y2);
void	draw_lines(t_game *game);
void	draw_user(t_game *game);
void	draw_map(t_game *game);

int cmp_sprites( const void* a, const void* b ); //static 
t_sprite* get_visible_sprites(t_game *game, int **vis, int* pcnt); //static 
void draw_sprites(t_game *game, int **vis, double zbuf[]); //static 

int get_wall_height(t_game *game, double dist);
void draw_wall(t_game *game, double wdist, int x, t_wall *wall, int tx);
// void draw_floor(t_game *game, double wdist, int x, t_wall *wall, int tx);
int sign( double d );
int map_get_cell(t_game *game, int x, int y);
bool get_wall_intersection(double ray, t_game *game, t_wall *wall, int **vis);

int key_press(int keycode, t_game *game);
int button_exit(int button, t_game *game);
int	button_press(int button, t_game *game);
int get_move_offset( double th, int key, double amt, double* pdx, double* pdy ); //static 
int player_move( t_game *game, int key, double amt );
void player_rotate(t_game *game, double th );

void decode_color(int color, int *r, int *g, int *b);
int encode_color(int r, int g, int b);
double get_luminosity(t_game *game, double dist);
int fade_color( int color, double lum );

double l2dist( double x0, double y0, double x1, double y1 );
double cast_single_ray( int x, t_game *game, t_wall *wall, int **vis);

void render(t_game *game);
int		draw_loop(t_game *game);

double is_zero(double d);
double deg2rad(double d);
double rad2deg(double d);
int max(int a, int b);
int min(int a, int b);

bool	user_dir(int c);

int	user_location(t_game *game);
int		param_chk(t_game *game, int argc, char **argv);
int		ext_check(char *argv, char *ext);
int		cub_check(t_game *game, char *argv, int fd);
int		ft_strerror(int err);
int		get_next_line(int fd, char **line);
int		check_resolution(t_game *game, char *line);

int		cub_check(t_game *game, char *argv, int fd);
int 	map_parsing(t_game *game, char *line);

int		check_colors(unsigned int *color, char *line, int *i);
int		check_texture(t_game *game, t_img *img, char *line, int *i);
int		get_xpmfile(t_game *game, t_img *img, char *file);


int		get_bitmap(t_game *game, int fd);
void	get_bitmapfile(t_game *game, int fd);
void	get_bitmapinfo(t_game *game, int fd);
void	get_bitmapdata(t_game *game, int fd);

#endif