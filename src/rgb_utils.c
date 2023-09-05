/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:47:24 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/05 19:04:30 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		*find_rgb(char *line);

int	valid_sep(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i] && !ft_isdigit(line[i]))
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count != 1);
}

int	count_nb_int(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			count++;
			while (line[i] && ft_isdigit(line[i]))
				i++;
			if (line[i] && count < 3 && valid_sep(&line[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (!line[i] && count == 3)
			return (EXIT_SUCCESS);
		else if (!line[i] && count != 3)
			return (EXIT_FAILURE);
		i++;
	}
	if (count > 3)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	rgb_is_valid(char *line)
{
	int		i;

	i = 1;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && \
			line[i] != ' ' && line[i] != '\n')
			return (false);
		i++;
	}
	if (count_nb_int(line) == EXIT_FAILURE)
		return (false);
	return (true);
}

int	ft_int_len(int nb)
{
	int		i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

int	fill_rgb(char *line, t_data *data)
{
	if (line[0] == 'F')
	{
		if (!data->rgb_floor)
			data->rgb_floor = find_rgb(line);
		else
		{
			ft_putstr_fd("Error\nMultiple RGB fill\n", 2);
			return (EXIT_FAILURE);
		}
	}
	else if (line[0] == 'C')
	{
		if (!data->rgb_ceiling)
			data->rgb_ceiling = find_rgb(line);
		else
		{
			ft_putstr_fd("Error\nMultiple RGB fill\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
