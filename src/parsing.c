#include "cub3d.h"
#include "libft.h"

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (1);
	if (file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (1);
	return (0);
}

int	check_input(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (ERROR_ARG);
	}
	else if (check_extension(av[1]))
	{
		printf("Error\nWrong file extension\n");
		return (ERROR_EXTENSION);
	}
	return (0);
}

int	check_data(t_data *data)
{
	(void)data;
	return (0);
}
