/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:42:51 by chmadran          #+#    #+#             */
/*   Updated: 2023/09/04 15:28:56 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static int	check_surrounding_walls(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (i == 0 || i == (int)ft_tablen(map) - 1)
			{
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (EXIT_FAILURE);
			}
			else if (j == 0 || j == (int)ft_strlen(map[i]) - 1)
			{
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

static int	check_invalid_character(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1'
				&& map[i][j] != 'N' && map[i][j] != 'S'
				&& map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_data_map(char **map)
{
	if (check_surrounding_walls(map))
		return (EXIT_FAILURE);
	if (check_invalid_character(map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
