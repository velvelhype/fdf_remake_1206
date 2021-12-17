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
#include "get_next_line/get_next_line.h"

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
    void    *mlx_ptr;
    void    *win_ptr;
    void    *image;
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

char    *file_to_str(char **argv);
void    str_to_t_fdf(t_fdf *fdf, char *save);
void    draw(t_fdf *fdf);
//checks
void    printf_point_matrix(t_fdf   *fdf);
int get_next_line(int fd, char **line);

#endif
