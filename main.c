#include "fdf.h"

int deal_key(int key, t_fdf *data)
{
    printf("%d\n", key);

    if(key == 24)
        data->zoom += 10;
    if(key == 27)
        data->zoom -= 10;
   if(key == 126)
        data->shift_y -= 40;
    if(key == 125)
        data->shift_y += 40;
   if(key == 123)
        data->shift_x -= 40;
    if(key == 124)
        data->shift_x += 40;
    if(key == 53)
        exit(1);
    mlx_clear_window(data->mlx_ptr, data->win_ptr);

    draw(data);
    return (0) ;
}

int main(int argc, char **argv)
{
    int fd = 0;

    if(argc != 2)
        exit(1);
    printf("%s\n", argv[1]);
    fd =  open(argv[1], O_RDONLY);

    int i = 0;
    int read_ret;

    t_fdf   fdf;
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1600, 1000, "Ikari Window");
    //init fdf datas
    fdf.rotation = 1;
    fdf.shift_x = 300;
    fdf.shift_y = 200;
    fdf.zoom = 20;
    //make t_fdf
    char buf[1];
    char *save;
    save = (char*)malloc(sizeof(char)*1000000);
    read_ret = read(fd, buf, 1);
    while(read_ret)
    {
        save[i] = *buf;
        i++;
        read_ret = read(fd, buf, 1);
    }
    save[i] = '\0';
    printf("save is \n %s\n", save);
    read_str_to_t_fdf(&fdf, save);
    draw(&fdf);
	mlx_hook(fdf.win_ptr, 2, 0, deal_key, &fdf);
    mlx_loop(fdf.mlx_ptr);
    //printf("x : %d y : %d\n", fdf.x, fdf.y);
}