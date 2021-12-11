#include "fdf.h"

void    printf_point_matrix(t_fdf   *fdf)
{
    printf("print_matrix::\n");
    for(int y = 0; y < fdf->y; y++)
    {
        for(int x = 0; x < fdf->x; x++)
            printf("%d\t", fdf->points[y][x].height);
            // printf("%d %d %d\n",y, x, fdf->points[y][x].height);
        printf("\n");
    }
}