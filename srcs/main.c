#include "cub3d.h"

int     main(void)
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
    mlx_loop(mlx);

}    