#include <stdio.h>
#include <OpenGL/gl.h>
#include "minilibx_macos/mlx.h"

int main()
{
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "Ikari Window");
 
    for(int x; x < 1000 ; x++)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x, 100, 1000);
    }
    mlx_loop(mlx_ptr);
}