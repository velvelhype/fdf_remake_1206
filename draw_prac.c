#include <stdio.h>
#include <OpenGL/gl.h>
#include "minilibx_macos/mlx.h"
#include "fdf.h"

void    put_pix(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
    *(unsigned int *)dst = color;
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Create Image");
    t_data img;
    img.img = mlx_new_image(mlx, 640, 360);
    

    img.addr = mlx_get_data_addr(img.img, &img.pix_bits,
    &img.line_len, &img.endi);
    put_pix(&img, 5, 5, 0x00FF00);
    mlx_put_image_to_window(mlx, win, img.img, 0, 0);
    mlx_loop(mlx);
}