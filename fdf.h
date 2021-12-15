#ifndef FDF_H
# define FDF_H
#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ?  -a : a)

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <OpenGL/gl.h>
#include "minilibx_macos/mlx.h"

// typedef struct  s_fdf
// {
//     int width;
//     int height;
//     int **z_matrix;
//     int zoom;
//     int color;
//     int shift_x;
//     int shift_y;
//     float rotation;
//     int twod_or_not_twod;
//     float maware;

//     void *mlx_ptr;
//     void *win_ptr;
// }       fdf;

typedef struct s_point
{
    int height;
    int color;
    float x;
    float y;
} t_point;

typedef struct s_fdf
{
    int     x;
    int     y;
    float   rotation;
    t_point **points;
    int     grid_len;
    void    *mlx_ptr;
    void    *win_ptr;
    double  lean_x;
    double  lean_y;
    int     shift_x;
    int     shift_y;
    int     zoom;
} t_fdf;

typedef struct s_color
{
	int red;
	int green;
	int blue;
} t_color;

void    read_str_to_t_fdf(t_fdf *fdf, char *save);

//checks
void    printf_point_matrix(t_fdf   *fdf);

void    draw(t_fdf *fdf);

#endif
