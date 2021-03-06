#include "fdf.h"

t_color	rgb_open(int color)
{
	t_color back;

	back.red = color / (256 * 256);
	color -= back.red * 256 * 256;
	back.green = color / (256);
	color -= back.green * 256;
	back.blue = color;

	return back;
}

int   rgb_zip(t_color col)
{
	int ret;
	ret = 0;
	ret += col.red * 256 * 256;
	ret += col.green * 256;
	ret += col.blue;

	return (ret);
}

int     make_color_step(int   a_color, int  b_color, int max)
{
	t_color col_step;
	t_color open_a = rgb_open(a_color);
	t_color open_b = rgb_open(b_color);

	if (max == 0)
		max = 1;
	int red_step = open_b.red - open_a.red;
	int blue_step = open_b.blue - open_a.blue;
	int green_step = open_b.green - open_a.green;
	col_step.red = red_step / max;
	col_step.green = green_step / max;
	col_step.blue = blue_step / max;

	return (rgb_zip(col_step));
}

void    make_isometric(t_point *dot, t_fdf *fdf)
{
	dot->x = (dot->x - dot->y) * cos(fdf->rotation);
	dot->y = (dot->x + dot->y) * sin(fdf->rotation) - dot->height;
}

void    coordinate_point(t_fdf *fdf, t_point *dot_a, t_point *dot_b)
{
	//make bigger
	dot_a->x *= fdf->zoom;
	dot_b->x *= fdf->zoom;
	dot_a->y *= fdf->zoom;
	dot_b->y *= fdf->zoom;
	dot_a->height  *= fdf->zoom;
	dot_b->height  *= fdf->zoom;
	//make isometrical
	make_isometric(dot_a, fdf);
	make_isometric(dot_b, fdf);
	//add positional shift to points for viewablility
	dot_a->x += fdf->shift_x;
	dot_b->x += fdf->shift_x;
	dot_a->y += fdf->shift_y;
	dot_b->y += fdf->shift_y;
}

void	paint_it_black(t_fdf *fdf)
{
	int pixel_bits;
    int line_bytes;
    int endian;
    char *buffer = mlx_get_data_addr(fdf->image,
    &pixel_bits, &line_bytes, &endian);

    int color = 0x000000;

    if (pixel_bits != 32)
        color = mlx_get_color_value(fdf->mlx_ptr, color);

    for(int y = 0; y < 1600; ++y)
        for(int x = 0; x < 1000; ++x)
        {
            int pixel = ((int)x * line_bytes) + ((int)y * 4);

            if (endian == 1)        // Most significant (Alpha) byte first
            {
                buffer[pixel + 0] = (color >> 24);
                buffer[pixel + 1] = (color >> 16) & 0xFF;
                buffer[pixel + 2] = (color >> 8) & 0xFF;
                buffer[pixel + 3] = (color) & 0xFF;
            }
            else 
			if (endian == 0)   // Least significant (Blue) byte first
            {
                buffer[pixel + 0] = (color) & 0xFF;
                buffer[pixel + 1] = (color >> 8) & 0xFF;
                buffer[pixel + 2] = (color >> 16) & 0xFF;
                buffer[pixel + 3] = (color >> 24);
            }
		}
}


void	my_pixel_put(t_fdf *fdf, t_point dot_a)
{
	int pixel_bits;
    int line_bytes;
    int endian;
    char *buffer = mlx_get_data_addr(fdf->image,
    &pixel_bits, &line_bytes, &endian);

    int color = 0xABCDEF;

    if (pixel_bits != 32)
        color = mlx_get_color_value(fdf->mlx_ptr, color);

    // for(int y = 0; y < 1000; ++y)
    //     for(int x = 0; x < 1600; ++x)
    //     {
            int pixel = ((int)dot_a.y * line_bytes) + ((int)dot_a.x * 4);

            if (endian == 1)        // Most significant (Alpha) byte first
            {
                buffer[pixel + 0] = (color >> 24);
                buffer[pixel + 1] = (color >> 16) & 0xFF;
                buffer[pixel + 2] = (color >> 8) & 0xFF;
                buffer[pixel + 3] = (color) & 0xFF;
            }
            else 
			if (endian == 0)   // Least significant (Blue) byte first
            {
                buffer[pixel + 0] = (color) & 0xFF;
                buffer[pixel + 1] = (color >> 8) & 0xFF;
                buffer[pixel + 2] = (color >> 16) & 0xFF;
                buffer[pixel + 3] = (color >> 24);
            }
		// }
}


void    draw_line(t_fdf *fdf, t_point dot_a, t_point dot_b)
{
	coordinate_point(fdf, &dot_a, &dot_b);
	//decide how carafully go to b_point
	float x_step = dot_b.x - dot_a.x;
	float y_step = dot_b.y - dot_a.y;
	int max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max; 
	y_step /= max;
	int color_step = make_color_step(dot_a.color, dot_b.color, max);
	// draw line by step
	while ((int)(dot_a.x - dot_b.x) || (int)(dot_a.y - dot_b.y))
	{
		// mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, dot_a.x, dot_a.y, dot_a.color);
		my_pixel_put(fdf, dot_a);
		dot_a.x += x_step;
		dot_a.y += y_step;
		dot_a.color += color_step;
	}
}

void    draw(t_fdf *fdf)
{
	// fdf->lean_x = 0.6;
	// fdf->lean_y = 0.6;
	printf("deaw1\n");
	paint_it_black(fdf);
	int x = 0;
	int y = 0;    
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