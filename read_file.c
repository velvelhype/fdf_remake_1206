#include "fdf.h"

int     count_axis(char    *save)
{
    int axis;

    axis = 0;
    while(*save != '\n')
    {
        if(ft_isdigit(*save))
            axis++;
        while(ft_isdigit(*save))
        {
            save++;
            if(*save == '\n')
                return (axis);
        }
        save++;
    }
    return (axis);
}

int     count_ordinary(char   *save)
{
    int ordinary;

    ordinary = 1;
    while(*save)
    {
        if(*save == '\n')
            ordinary++;
        save++;
    }
    return (ordinary);
}

int     char_atoi(char a, int height)
{
    // printf("c_a:: c%c h:%d\n", a, height);
    a = a - 48;
    height = height * 10 + a;

    return (height);
}

int    get_height(char *save, int *bookmark)
{
    int height;

    height = 0;
    while(*(save + *bookmark) == ' ' || *(save + *bookmark) == '\n')
        (*bookmark)++;
    while(ft_isdigit(*(save + *bookmark)))
    {
        // printf("g_h c:: %c b::%d\n", *(save + *bookmark), *bookmark);
        height = char_atoi(*(save + *bookmark), height);
        (*bookmark)++;
    }
    return  height;
}

void    make_matrix(t_fdf *fdf, char* save)
{
    fdf->points = (t_point**)malloc(sizeof(t_point*) * fdf->y);
    if(!(fdf->points))
        exit(1);
    int y_count;
    y_count = 0;
    while(y_count < fdf->y)
    {
        *(fdf->points + y_count) = (t_point*)malloc(sizeof(t_point) * fdf->x);
        if(!*(fdf->points + y_count))
            exit(1);
        y_count++;
    }
    int x_count;
    x_count = 0;
    y_count = 0;
    int bookmark;
    bookmark = 0;
    while(y_count < fdf->y)
    {
        while(x_count < fdf->x)
        {
            printf("m_m y:%d, x:%d bm:%d\n", y_count, x_count, bookmark);
            (fdf->points)[y_count][x_count].height = get_height(save, &bookmark);
            (fdf->points)[y_count][x_count].x =  x_count;
            (fdf->points)[y_count][x_count].y =  y_count;
            x_count++;
        }
        y_count++;
        x_count = 0;
    }
}

void    read_str_to_t_fdf(t_fdf *fdf, char *save)
{
    printf("in read_str_to_t_fdf :\n%s\n", save);
    fdf->x = count_axis(save);
    fdf->y = count_ordinary(save);
    printf("axis is %d\n", fdf->x);
    printf("ordinary is %d\n", fdf->y);
    make_matrix(fdf, save);
    printf_point_matrix(fdf);
}
