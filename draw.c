#include "fdf.h"

void    draw_right(t_fdf *fdf, int x, int y)
{
    int offset = 0;
    while(offset < fdf->grid_len)
    {
        mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr,
         (x * fdf->grid_len) + offset,
          y * fdf->grid_len,
           1000);
        offset++;
    }
}

void    draw_under(t_fdf *fdf, int x, int y)
{
    float lean_y = 0.5;

    int offset = 0;
    while(offset < fdf->grid_len)
    {
        mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, 
        x * fdf->grid_len,
         ((y * fdf->grid_len) + offset) * lean_y,
          1000);
        // x * fdf->grid_len, (y * fdf->grid_len) + offset, 1000);
        offset++;
    }
}

void    draw(t_fdf *fdf)
{


    printf("let's draw\n");
    fdf->mlx_ptr = mlx_init();
    fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1000, 1000, "Ikari Window");

    fdf->grid_len = 50;

    int x = 0;
    int y = 0;
    while(y < fdf->y)
    {
        while(x < fdf->x)
        {
            printf("y: %d x: %d\n", y, x);
            if(x != fdf->x -1)
                draw_right(fdf, x, y);
            if(y != fdf->y -1)
                draw_under(fdf, x, y);
            x++;
        }
        x = 0;
        y++;  
    }

    mlx_loop(fdf->mlx_ptr);
}