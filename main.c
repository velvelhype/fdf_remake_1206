#include "fdf.h"

int	deal_key(int key, t_fdf *data)
{
	printf("%d\n", key);

	if (key == 24)
		data->zoom += 1;
	if (key == 27)
		data->zoom -= 1;
	if (key == 126)
		data->shift_y -= 40;
	if (key == 125)
		data->shift_y += 40;
	if (key == 123)
		data->shift_x -= 40;
	if (key == 124)
		data->shift_x += 40;
	if (key == 53)
		exit(1);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0) ;
}

void    init_fdf(t_fdf  *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1600, 1000, "Ikari Window");
	fdf->rotation = 1;
	fdf->shift_x = 700;
	fdf->shift_y = 500;
	fdf->zoom = 10;   
}

int main(int argc, char **argv)
{

	if(argc != 2)
		exit(1);

	char	*save;
	save = file_to_str(argv);
	printf("save is \n %s\n", save);
	t_fdf	fdf;
	init_fdf(&fdf);
	str_to_t_fdf(&fdf, save);
	draw(&fdf);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf);
	mlx_loop(fdf.mlx_ptr);
}
