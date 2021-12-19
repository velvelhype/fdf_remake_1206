#include "fdf.h"

void	paint_it_black(t_fdf *fdf)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;

	buffer = mlx_get_data_addr(fdf->image, &pixel_bits, &line_bytes, &endian);
    int color;

	color = 0x000000;
    for(int y = 0; y < 1600; ++y)
        for(int x = 0; x < 1000; ++x)
        {
            int pixel = ((int)x * line_bytes) + ((int)y * 4);
			// if (endian == 1)
			// {
			//     buffer[pixel + 0] = (color >> 24);
			//     buffer[pixel + 1] = (color >> 16) & 0xFF;
			//     buffer[pixel + 2] = (color >> 8) & 0xFF;
			//     buffer[pixel + 3] = (color) & 0xFF;
			// }
			// else 
			if (endian == 0)
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
	int		pixel_bits;
    int		line_bytes;
    int		endian;
    char	*buffer;
	int		color;

	buffer = mlx_get_data_addr(fdf->image,
    &pixel_bits, &line_bytes, &endian);
    color = dot_a.color;
	if (dot_a.x > 1600 || dot_a.y > 1000)
		return ;
	if (dot_a.x <= 0 || dot_a.y <= 0)
		return ;
    int pixel;
	pixel = ((int)dot_a.y * line_bytes) + ((int)dot_a.x * 4);
    // if (endian == 1)
    // {
	// 	buffer[pixel + 0] = (color >> 24);
	// 	buffer[pixel + 1] = (color >> 16) & 0xFFFFFF;
	// 	buffer[pixel + 2] = (color >> 8) & 0xFFFFFF;
	// 	buffer[pixel + 3] = (color) & 0xFFFFFF;
    // }
    // else
	 if (endian == 0)
	{
		buffer[pixel + 0] = (color) & 0xFFFFFF;
		buffer[pixel + 1] = (color >> 8) & 0xFFFFFF;
		buffer[pixel + 2] = (color >> 16) & 0xFFFFFF;
		buffer[pixel + 3] = (color >> 24);
    }
}