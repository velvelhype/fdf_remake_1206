#include "fdf.h"

void	put_pix(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int *)dst = color;
}

void	paint_it_black(t_fdf *fdf)
{
	t_data	im;
	int		color;
	int		x;
	int		y;

	im.img = fdf->image;
	im.addr = mlx_get_data_addr(im.img, &im.pix_bits, &im.line_len, &im.endi);
	color = 0x000000;
	x = -1;
	y = -1;
	while (y++ <= 1000)
	{
		while (x++ <= 1600)
		{
			put_pix(&im, x, y, color);
		}
		x = 0;
	}
}

void	my_pixel_put(t_fdf *fdf, t_point dot_a)
{
	t_data	im;

	if (dot_a.x < 0 || dot_a.x > 1600)
		return ;
	if (dot_a.y < 0 || dot_a.y > 1000)
		return ;
	im.img = fdf->image;
	im.addr = mlx_get_data_addr(im.img, &im.pix_bits, &im.line_len, &im.endi);
	put_pix(&im, dot_a.x, dot_a.y, dot_a.color);
}
