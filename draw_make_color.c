#include "fdf.h"

t_color	rgb_open(int color)
{
	t_color	back;

	back.red = color / (256 * 256);
	color -= back.red * 256 * 256;
	back.green = color / (256);
	color -= back.green * 256;
	back.blue = color;
	return (back);
}

int	rgb_zip(t_color col)
{
	int	ret;

	ret = 0;
	ret += col.red * 256 * 256;
	ret += col.green * 256;
	ret += col.blue;
	return (ret);
}

int	make_step(int a_color, int b_color, int max)
{
	int	step;
	int	ret;

	step = b_color - a_color;
	ret = step / max;
	return (ret);
}

int	make_color_step(int a_color, int b_color, int max)
{
	t_color	col_step;
	t_color	open_a;
	t_color	open_b;

	open_a = rgb_open(a_color);
	open_b = rgb_open(b_color);
	if (max == 0)
		max = 1;
	col_step.red = make_step(open_a.red, open_b.red, max);
	col_step.green = make_step(open_a.green, open_b.green, max);
	col_step.blue = make_step(open_a.blue, open_b.blue, max);
	return (rgb_zip(col_step));
}
