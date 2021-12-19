#include "fdf.h"

int	char_xtoi(char a, int color)
{
	if (a == 'A')
		a = 10;
	else if (a == 'B')
		a = 11;
	else if (a == 'C')
		a = 12;
	else if (a == 'D')
		a = 13;
	else if (a == 'E')
		a = 14;
	else if (a == 'F')
		a = 15;
	else
		a = a - 48;
	color = color * 16 + a;
	return (color);
}

int	get_color(char *save, int *clip)
{
	int	i;

	*clip += 3;
	i = 0;
	while (*(save + *clip) != ' ')
	{
		if (*(save + *clip) == '\n' || *(save + *clip) == '\0')
			break ;
		i = char_xtoi(*(save + *clip), i);
		(*clip)++;
	}
	return (i);
}

void	fill_matrix(char *save, t_fdf *fdf, int x_count, int y_count)
{
	int	clip;

	clip = 0;
	while (y_count < fdf->y)
	{
		while (x_count < fdf->x)
		{
			(fdf->points)[y_count][x_count].height = get_height(save, &clip);
			if (save[clip] == ',')
			{
				(fdf->points)[y_count][x_count].color = get_color(save, &clip);
			}
			else
				(fdf->points)[y_count][x_count].color = 0xFFFFFF;
			(fdf->points)[y_count][x_count].x = x_count;
			(fdf->points)[y_count][x_count].y = y_count;
			x_count++;
		}
		y_count++;
		x_count = 0;
	}
}

void	make_matrix(t_fdf *fdf, char *save)
{
	int	y_count;
	int	x_count;

	fdf->points = (t_point **)malloc(sizeof(t_point *) * fdf->y);
	if (!(fdf->points))
		exit(1);
	y_count = 0;
	while (y_count < fdf->y)
	{
		*(fdf->points + y_count) = (t_point *)malloc(sizeof(t_point) * fdf->x);
		if (!*(fdf->points + y_count))
			exit(1);
		y_count++;
	}
	x_count = 0;
	y_count = 0;
	fill_matrix(save, fdf, x_count, y_count);
}

void	str_to_t_fdf(t_fdf *fdf, char *save)
{
	fdf->x = count_axis(save);
	fdf->y = count_ordinary(save);
	make_matrix(fdf, save);
	free(save);
}
