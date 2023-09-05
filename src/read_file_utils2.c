/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:36:04 by chmadran          #+#    #+#             */
/*   Updated: 2023/09/05 14:17:31 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_start(t_data *data, char *line, char *map)
{
	int	i;

	i = 0;
	if (data->no_tex_path && data->so_tex_path && data->we_tex_path
		&& data->ea_tex_path && data->rgb_floor && data->rgb_ceiling)
		return (EXIT_SUCCESS);
	if (map && map[i])
	{
		while (line[i])
		{
			if (line[i] == '\n' && line[i + 1] && line[i + 1] == '\n')
				return (EXIT_FAILURE);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	check_line(char *line)
{
	if (line && (line[0] == '1' || line[0] == ' ' || line[0] == '0'
			|| line[0] == '\n' || line[0] == '\t'))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	ft_longest_len_tab(char **map)
{
	int		i;
	int		temp_len;
	int		longest_len;

	i = -1;
	longest_len = 0;
	temp_len = 0;
	while (map[++i])
	{
		temp_len = ft_strlen(map[i]);
		if (temp_len > longest_len)
			longest_len = temp_len;
	}
	return (longest_len);
}
