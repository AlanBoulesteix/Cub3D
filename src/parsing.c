/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:32:53 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/27 15:45:12 by aboulest         ###   ########.fr       */
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
	if (file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (1);
	return (0);
}

int	check_input(int ac, char **av)
{
	if (ac != 2)
		return (printf_error(ERROR_ARG));
	else if (check_extension(av[1]))
		return (printf_error(ERROR_EXTENSION));
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
			return (printf_error(ERROR_RGB));
	}
	i = -1;
	while (++i < 3)
	{
		if (!data->rgb_floor
			|| (data->rgb_floor[i] < 0 || data->rgb_ceiling[i] > 255))
			return (printf_error(ERROR_RGB));
	}
	return (0);
}

int	check_map(char **map)
{
	(void)map;
	return (0);
}

int	check_data(t_data *data)
{
	if (check_rgb(data))
		return (1);
	if (check_map(data->map))
		return (printf_error(ERROR_MAP));
	return (0);
}
