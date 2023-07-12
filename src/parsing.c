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

int	check_rgb(t_data *data)
{
	int	i;

	i = -1;

	while (++i < 3)
	{
		if (!data->rgb_ceiling
			|| (data->rgb_ceiling[i] < 0 || data->rgb_ceiling[i] > 255))
			return(ERROR_RGB);
	}
	i = -1;
	while (++i < 3)
	{
		if (!data->rgb_floor 
			|| (data->rgb_floor[i] < 0 || data->rgb_ceiling[i] > 255))
			return(ERROR_RGB);
	}
	return (0);
}

int	check_map(char **map)
{
	char	*dup_map;

	
}

int	check_data(t_data *data)
{
	if (check_rgb(data))
	{
		printf("Error\nWrong RGB values\n");
		return (ERROR_RGB);
	}
	if (check_map(data->map))
	{
		printf("Error\nSomething went wrong with map\n");
		return (ERROR_MAP);
	}
	return (0);
}
