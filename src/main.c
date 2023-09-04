/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:09:44 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/04 15:44:01 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	printf_error(int error)
{
	if (error == ERROR_ARG)
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
	else if (error == ERROR_EXTENSION)
		ft_putstr_fd("Error\nWrong file extension\n", 2);
	else if (error == ERROR_RGB)
		ft_putstr_fd("Error\nWrong RGB\n", 2);
	else if (error == ERROR_MAP)
		ft_putstr_fd("Error\nWrong map\n", 2);
	else if (error == ERROR_MALLOC)
		ft_putstr_fd("Error\nMalloc failed\n", 2);
	else if (error == ERROR_MLX)
		ft_putstr_fd("Error\nMlx failed\n", 2);
	else if (error == ERROR_TEXT)
		ft_putstr_fd("Error\nWrong texture\n", 2);
	else if (error == ERROR_EMPTY_LINE)
		ft_putstr_fd("Error\nEmpty line in map\n", 2);
	return (EXIT_FAILURE);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	if (check_input(ac, av))
		return (EXIT_FAILURE);
	data = read_file(av[1]);
	if (!data)
		return (EXIT_FAILURE);
	if (check_data(data))
		return (free_data(data), EXIT_FAILURE);
	print_data(data);
	game(data);
	free_data(data);
}
