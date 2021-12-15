#include "fdf.h"

void    make_isometric(t_point *dot, t_fdf *fdf)
{
    dot->x = (dot->x - dot->y) * cos(fdf->rotation);
    dot->y = (dot->x + dot->y) * sin(fdf->rotation) - dot->height;
}

void    draw_line(t_fdf *fdf, t_point dot_a, t_point dot_b)
{
    //make bigger
    dot_a.x *= fdf->zoom;
    dot_b.x *= fdf->zoom;
    dot_a.y *= fdf->zoom;
    dot_b.y *= fdf->zoom;

    //make isometrical
    make_isometric(&dot_a, fdf);
    make_isometric(&dot_b, fdf);

    //add positional shift to points for viewablility
    dot_a.x += fdf->shift_x;
    dot_b.x += fdf->shift_x;
    dot_a.y += fdf->shift_y;
    dot_b.y += fdf->shift_y;

    //decide how carafully go to b_point
    float x_step = dot_b.x - dot_a.x;
    float y_step = dot_b.y - dot_a.y;
    int max = MAX(MOD(x_step), MOD(y_step));
    x_step /= max; 
    y_step /= max;

    // draw line by step
    while((int)(dot_a.x - dot_b.x) || (int)(dot_a.y - dot_b.y))
    {
        mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, dot_a.x, dot_a.y, 0x00FF00);
        dot_a.x += x_step;
        dot_a.y += y_step;
    }
}

void    draw(t_fdf *fdf)
{
    printf("let's draw\n");

    fdf->grid_len = 50;
    fdf->lean_x = 0.6;
    fdf->lean_y = 0.6;

    int x = 0;
    int y = 0;    
    while(y < fdf->y)
    {
        while(x < fdf->x)
        {
            // printf("y: %f x: %f\n", y, x);
            if(x < fdf->x - 1)
                draw_line(fdf, fdf->points[y][x], fdf->points[y][x + 1]);
            if(y < fdf->y - 1)
                draw_line(fdf, fdf->points[y][x], fdf->points[y + 1][x]);
            x++;
        }
        x = 0;
        y++;  
    }
}