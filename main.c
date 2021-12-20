#include "fdf.h"

int	deal_key(int key, t_fdf *fdf)
{
	if (key == 20)
		fdf->is_threeD = 1;
	if (key == 19)
		fdf->is_threeD = 0;
	if (key == 14)
		fdf->rotation += 0.03;
	if (key == 15)
		fdf->rotation -= 0.03;
	if (key == 24)
		fdf->zoom += 1;
	if (key == 27)
		fdf->zoom -= 1;
	if (key == 126)
		fdf->shift_y -= 40;
	if (key == 125)
		fdf->shift_y += 40;
	if (key == 123)
		fdf->shift_x -= 40;
	if (key == 124)
		fdf->shift_x += 40;
	if (key == 53)
		exit(1);
	draw(fdf);
	return (0);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1600, 1000, "fdf");
	fdf->image = mlx_new_image(fdf->mlx_ptr, 1600, 1000);
	fdf->is_threeD = 1;
	fdf->rotation = 1;
	fdf->shift_x = 700;
	fdf->shift_y = 500;
	fdf->zoom = 10;
}

int	main(int argc, char **argv)
{
	char	*save;
	t_fdf	fdf;

	if (argc != 2)
		exit(1);
	save = file_to_str(argv);
	init_fdf(&fdf);
	str_to_t_fdf(&fdf, save);
	draw(&fdf);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
