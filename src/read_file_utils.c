/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:05:13 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/05 10:37:17 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*find_rgb(char *line, char identifier)
{
	int	i;
	int	k;
	int	*rgb;

	i = 0;
	k = 0;
	rgb = malloc(sizeof(int) * 3);
	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;
	while (line[i] && line[i] != identifier)
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && line[i + 3])
		{
			rgb[k++] = ft_atoi(&line[i]);
			while (k < 3 && line[i] && ft_isdigit(line[i]))
				i++;
		}
		if (!line[i])
			return (rgb);
		i++;
	}
	return (rgb);
}

static int	find_side_texture(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (NORTH);
	else if (line[0] == 'S' && line[1] == 'O')
		return (SOUTH);
	else if (line[0] == 'W' && line[1] == 'E')
		return (WEST);
	else if (line[0] == 'E' && line[1] == 'A')
		return (EAST);
	else
		return (ERROR);
}

int	check_side_texture(char *str, int side)
{
	return (ft_strlen(str) > 2 && find_side_texture(str) == side);
}

int	check_texture(t_data *data)
{
	return (!data->no_tex_path || !data->so_tex_path
		|| !data->we_tex_path || !data->ea_tex_path);
}
