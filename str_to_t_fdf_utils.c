#include "fdf.h"

int	count_axis(char	*save)
{
	int	axis;

	axis = 0;
	while (*save != '\n')
	{
		if (ft_isdigit(*save))
			axis++;
		while (ft_isascii(*save) && *save != ' ')
		{
			save++;
			if (*save == '\n')
				return (axis);
		}
		save++;
	}
	return (axis);
}

int	count_ordinary(char *save)
{
	int	ordinary;

	ordinary = 1;
	while (*save)
	{
		if (*save == '\n')
			ordinary++;
		save++;
	}
	return (ordinary);
}

int	char_atoi(char a, int height)
{
	a = a - 48;
	height = height * 10 + a;
	return (height);
}

int	get_height(char *save, int *bookmark)
{
	int	height;

	height = 0;
	while (*(save + *bookmark) == ' ' || *(save + *bookmark) == '\n')
		(*bookmark)++;
	while (ft_isdigit(*(save + *bookmark)))
	{
		height = char_atoi(*(save + *bookmark), height);
		(*bookmark)++;
	}
	return (height);
}
