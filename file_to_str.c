#include "fdf.h"

void	ft_strncpy(char *dst, char *src, size_t	n)
{
	while(n > 0)
	{
		dst[n - 1] = src[n - 1];
		n--;
	}
}

char	*read_to_save(int fd, int stack_size, char *save)
{
	int read_ret;
	char buf[1];
	read_ret = read(fd, buf, 1);
	size_t	i;
	i = 0;
	char *new;

	while(read_ret)
	{
		if((i % stack_size) == 0)
		{
			new = (char*)malloc(sizeof(char) * (i + stack_size + 1));
			ft_strncpy(new, save, i);
			free(save);
			save = new;
		}
		save[i] = *buf;
		i++;
		read_ret = read(fd, buf, 1);
	}
	save[i] = '\0';
	return (save);
}

char    *file_to_str(char **argv)
{
	int fd;
	int	stack_size;
	char *save;

	fd = 0;
	stack_size = 50000;
	fd =  open(argv[1], O_RDONLY);
	save = (char*)malloc(sizeof(char) * stack_size + 1);
	save = read_to_save(fd, stack_size, save);
	return  (save);
}