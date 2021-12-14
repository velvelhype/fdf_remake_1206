#include "fdf.h"

void    draw_right(t_fdf *fdf, int x, int y)
{
    int offset = 0;
    while(offset < fdf->grid_len)
    {
        mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr,
         (x * fdf->grid_len) + offset, y * fdf->grid_len, 1000);
        offset++;
    }
}

void    draw_under(t_fdf *fdf, int x, int y)
{
    int offset = 0;

    while(offset < fdf->grid_len)
    {
        mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, 
        x * fdf->grid_len , (y * fdf->grid_len) + offset, 1000);
        offset++;
    }
}

#include <math.h>
void    draw(t_fdf *fdf)
{
    fdf->grid_len = 100;
    float lean_x = 0.5;
    float lean_y = 0.5;
    printf("let's draw\n");
    fdf->mlx_ptr = mlx_init();
    fdf->win_ptr = mlx_new_window(fdf->mlx_ptr,
    1000, 1000, "Ikari Window");
    for(int ang = 0; ang < 360 ; ang++)
        mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, 
        500 + cos(ang) * fdf->grid_len * lean_x,
        500 + sin(ang) * fdf->grid_len * lean_y, 1000);

    for(int ang = 0; ang < 360; ang++)
    {
        for(int x = 0; x < fdf->grid_len; x++)
            mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, 
            500 + cos(ang) * x * lean_x,
            500 + sin(ang) * x * lean_y, 1000);
    }

    printf("pra done\n");
    mlx_loop(fdf->mlx_ptr);
}