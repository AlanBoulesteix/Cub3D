/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:42:51 by chmadran          #+#    #+#             */
/*   Updated: 2023/09/05 11:34:52 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	check_map_empty_line(char *map)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (i > 0 && map[i] == '\n' && map[i + 1] && map[i + 1] == '\n')
		{
			printf_error(ERROR_EMPTY_LINE);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
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
			if (map[i][j] == '0')
			{
				if (check_character(map[i - 1][j])
					|| check_character(map[i - 1][j - 1])
					|| check_character(map[i - 1][j + 1])
					|| check_character(map[i][j - 1])
					|| check_character(map[i][j + 1])
					|| check_character(map[i + 1][j])
					|| check_character(map[i + 1][j - 1])
					|| check_character(map[i + 1][j + 1]))
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

static int	check_count_characters(char **map)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				count++;
		}
	}
	if (count > 1 || count == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_data_map(char **map)
{
	if (check_surrounding_walls(map))
		return (EXIT_FAILURE);
	if (check_count_characters(map))
		return (EXIT_FAILURE);
	if (check_invalid_character(map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
