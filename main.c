#include "fdf.h"

int main(int argc, char **argv)
{
    int fd = 0;

    if(argc != 2)
        exit(1);
    printf("%s\n", argv[1]);
    fd =  open(argv[1], O_RDONLY);

    int i = 0;
    int read_ret;
    char buf[1];
    char save[100000];
    read_ret = read(fd, buf, 1);
    while(read_ret)
    {
        save[i] = *buf;
        i++;
        read_ret = read(fd, buf, 1);
    }
    t_fdf   fdf;
    read_file(&fdf, save);
    draw(&fdf);
    // printf("x : %d y : %d\n", fdf.x, fdf.y);
}