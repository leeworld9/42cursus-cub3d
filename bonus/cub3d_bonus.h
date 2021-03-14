/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:48:13 by dohelee           #+#    #+#             */
/*   Updated: 2021/03/15 02:42:18 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define BUFFER_SIZE 4096
# define OPEN_MAX 256

# define BYTES_PER_PIXEL 4
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define EPS 1e-06
# define FOV 60
# define WALL_H 1.0
# define MAPX 11
# define MAPY 15
# define ROTATE_UNIT 0.06
# define MOVE_UNIT 0.15
# define TILE_SIZE 7
# define USER_SIZE 2
# define USER_PAD 30

# define KEY_PRESS_EVNT 2
# define BUTTON_PRESS_EVNT 4
# define EXIT_EVNT 33

typedef struct		s_img
{
	void			*i;
	unsigned int	*d;
	int				w;
	int				h;
	int				b;
	int				l;
	int				e;
	unsigned int	color;
}					t_img;

typedef struct		s_sprite
{
	int				sx;
	int				sy;
	double			dist;
	double			th;
}					t_sprite;

typedef enum		e_dir
{
	DIR_N = 0,
	DIR_E,
	DIR_W,
	DIR_S
}					t_dir;

typedef struct		s_wall
{
	double			wx;
	double			wy;
	t_dir			wdir;
}					t_wall;

typedef struct		s_win
{
	void			*w;
	int				x;
	int				y;
	int				max_x;
	int				max_y;
}					t_win;

typedef struct		s_map
{
	char			**map;
	int				mx;
	int				my;
	int				chk;
}					t_map;

typedef struct		s_draw_wfc
{
	int				y0;
	int				y1;
	int				ystart;
	int				yend;
	double			h;
	double			dh;
	double			d_ratio;
	double			fx;
	double			fy;
	double			lum;
}					t_draw_wfc;

typedef struct		s_draw_sp
{
	int				x;
	int				y;
	int				sh;
	double			angle;
	int				cx;
	int				xmin;
	int				xmax;
	double			txratio;
	int				tx;
	int				y0;
	int				ty;
	int				color;
	double			lum;
}					t_draw_sp;

typedef enum		e_hitside
{
	VERT,
	HORIZ
}					t_hitside;

typedef struct		s_ray
{
	t_hitside		hs;
	int				xstep;
	int				ystep;
	double			xslope;
	double			yslope;
	double			nx;
	double			ny;
	double			fx;
	double			gx;
	int				mapx;
	int				mapy;
	bool			hit;
}					t_ray;

typedef struct		s_game
{
	void			*mlx;
	t_win			win;
	t_map			map;
	double			fov_v;
	double			pixel_per_angle;
	double			angle_per_pixel;
	t_img			img;
	t_img			floor;
	t_img			ceiling;
	t_img			sprite;
	t_sprite		*sparr;
	int				nsp;
	t_wall			wall;
	t_img			wall_n;
	t_img			wall_s;
	t_img			wall_w;
	t_img			wall_e;
	double			px;
	double			py;
	double			th;
	int				err_chk;
	t_img			m;
}					t_game;

int					render(t_game *g);
int					draw_loop(t_game *g);
int					get_tx(t_game *get_wall_height);

void				init_draw_sp(t_draw_sp *dsp);
void				init_draw_wfc(t_draw_wfc *dwfc);
void				init_sprite(t_sprite *sp);
void				cub_init(t_game *g);
void				cub_set(t_game *g);

int					**malloc_2d(int i, int j);
int					free_2d_i(int **arr, int j, int errnum);
int					free_2d_c(char **arr, int j, int errnum);
void				memset_2d(int **arr, int x, int y, int c);
void				cub_close(t_game *g);

int					get_wall_height(t_game *g, double dist);
int					map_get_cell(t_game *g, int x, int y);
void				draw_wall(t_game *g, double wdist, int x, int tx);
int					get_wall_tex(t_game *g, int tx, int ty);

void				draw_floor_ceiling(t_game *g, double wdist, int x);

void				set_ray_variable(double ray, t_game *g, t_ray *r);
bool				get_wall_intersection(double ray, t_game *g, int **vis);
t_hitside			find_hitmap(t_game *g, t_ray *r, int *mapx, int *mapy);
bool				hit_location(t_game *g, t_ray *r);
double				cast_single_ray(int x, t_game *g, int **visiable);

int					sign(double d);
double				l2dist(double x0, double y0, double x1, double y1);
double				check_angle(int angle);

int					get_next_line(int fd, char **line);

double				is_zero(double d);
double				deg2rad(double d);
double				rad2deg(double d);
int					max(int a, int b);
int					min(int a, int b);

void				decode_color(int color, int *r, int *g, int *b);
int					encode_color(int r, int g, int b);
double				get_luminosity(t_game *g, double dist);
int					fade(int color, double lum);

t_sprite			*visspr_malloc(t_sprite *before_sparr, t_sprite sp, int n);
void				get_vis_sprites(t_game *g, t_sprite **s, int **v, int *n);
void				sort_sprite(t_sprite *sparr, int cnt);
void				draw_sp_texture(t_game *g, t_draw_sp *d, int i, double z[]);
void				draw_sprites(t_game *g, int **vis, double zbuf[]);

int					cub_parsing(t_game *g, char *line);
int					check_resolution(t_game *g, char *line);
int					check_texture(t_game *g, t_img *img, char *line, int *i);
int					check_map(t_game *g, char *line, int *i);

int					remove_space(char *line, int *i);
int					get_xpmfile(t_game *g, t_img *img, char *file);
char				*get_line(t_game *g, char *line, int *i);
int					line_length(t_game *g, char *line);
bool				check_num(char *str);

bool				user_dir(int c);
int					user_deg(int c);
int					user_location(t_game *g);
int					user_errchk(int chk);

int					param_check(t_game *g, int argc, char **argv);
int					ext_check(char *argv, char *ext);
int					wall_check(t_game *g);
int					cub_check(t_game *g, char *argv, int fd);
int					ft_strerror(int err);

void				get_bitmapdata(t_game *g, int fd);
void				get_bitmapinfo(t_game *g, int fd);
void				get_bitmapfile(t_game *g, int fd);
int					get_bitmap(t_game *g, int fd);

int					key_press(int key, t_game *game);
int					event_exit(void);
int					move_offset(double th, int key, double *pdx, double *pdy);
int					player_move(t_game *game, int key);
void				player_rotate(t_game *game, double th);

void				draw_f_texture(t_game *g, t_draw_wfc *dwfc, int x, int y);
void				draw_c_texture(t_game *g, t_draw_wfc *dwfc, int x, int y);

void				draw_map(t_game *g);

int					button_press(int button, int x, int y, t_game *g);

#endif
