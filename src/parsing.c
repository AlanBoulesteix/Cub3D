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

int	check_map(char *str)
{
	return(read_file(str));
}

int	check_input(int ac, char **av)
{
	if (ac != 2)
		return (ERROR_ARG);
	else if (check_extension(av[1]))
		return (ERROR_EXTENSION);
	else if (check_map(av[1]))
		return (ERROR_MAP);
	return (0);
}

void	printf_error(int error)
{
	if (error == ERROR_ARG)
		printf("Error\nWrong number of arguments\n");
	else if (error == ERROR_EXTENSION)
		printf("Error\nWrong file extension\n");
	else if (error == ERROR_MAP)
		printf("Error\nWrong map\n");
}

int main(int ac, char *av[])
{
	int		error;

	error = check_input(ac, av);
	if (error)
		printf_error(error);
	else
		printf("OK\n");
}
