/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:32:53 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/04 14:15:20 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (1);
	if (ft_strncmp(file + len - 4, ".cub", 4))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_input(int ac, char **av)
{
	if (ac != 2)
		return (printf_error(ERROR_ARG));
	else if (check_extension(av[1]))
		return (printf_error(ERROR_EXTENSION));
	return (EXIT_SUCCESS);
}

int	check_rgb(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (!data->rgb_ceiling
			|| (data->rgb_ceiling[i] < 0 || data->rgb_ceiling[i] > 255))
			return (printf_error(ERROR_RGB));
	}
	i = -1;
	while (++i < 3)
	{
		if (!data->rgb_floor
			|| (data->rgb_floor[i] < 0 || data->rgb_ceiling[i] > 255))
			return (printf_error(ERROR_RGB));
	}
	return (EXIT_SUCCESS);
}

int	check_map(char **map)
{
	(void)map;
	return (EXIT_SUCCESS);
}

int	check_data(t_data *data)
{
	if (check_rgb(data))
		return (1);
	if (check_map(data->map))
		return (printf_error(ERROR_MAP));
	return (0);
}
