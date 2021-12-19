#include "fdf.h"

void	make_isometric(t_point *dot, t_fdf *fdf)
{
	dot->x = (dot->x - dot->y) * cos(fdf->rotation);
	dot->y = (dot->x + dot->y) * sin(fdf->rotation) - dot->height;
}

void	coordinate_point(t_fdf *fdf, t_point *dot_a, t_point *dot_b)
{
	dot_a->x *= fdf->zoom;
	dot_b->x *= fdf->zoom;
	dot_a->y *= fdf->zoom;
	dot_b->y *= fdf->zoom;
	dot_a->height *= fdf->zoom;
	dot_b->height *= fdf->zoom;
	if (fdf->is_threeD)
	{
		make_isometric(dot_a, fdf);
		make_isometric(dot_b, fdf);
	}
	dot_a->x += fdf->shift_x;
	dot_b->x += fdf->shift_x;
	dot_a->y += fdf->shift_y;
	dot_b->y += fdf->shift_y;
}

void	draw_line(t_fdf *fdf, t_point dot_a, t_point dot_b)
{
	float	x_step;
	float	y_step;
	int		max;
	int		color_step;

	coordinate_point(fdf, &dot_a, &dot_b);
	x_step = dot_b.x - dot_a.x;
	y_step = dot_b.y - dot_a.y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	color_step = make_color_step(dot_a.color, dot_b.color, max);
	while ((int)(dot_a.x - dot_b.x) || (int)(dot_a.y - dot_b.y))
	{
		my_pixel_put(fdf, dot_a);
		dot_a.x += x_step;
		dot_a.y += y_step;
		dot_a.color += color_step;
	}
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	paint_it_black(fdf);
	while (y < fdf->y)
	{
		while (x < fdf->x)
		{
			if (x < fdf->x - 1)
				draw_line(fdf, fdf->points[y][x], fdf->points[y][x + 1]);
			if (y < fdf->y - 1)
				draw_line(fdf, fdf->points[y][x], fdf->points[y + 1][x]);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->image, 0, 0);
}
