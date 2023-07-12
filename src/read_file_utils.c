/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:05:13 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/12 15:41:24 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int *find_rgb(char *line) //@TODO: check if not int 
{
	int	*rgb;

	rgb = malloc(sizeof(int) * 3);
	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;
	if (ft_strlen(line) < 8 || ft_strlen(line) > 14)
		return (rgb);
	rgb[0] = ft_atoi(line + 2);
	rgb[1] = ft_atoi(line + 2 + ft_intlen(rgb[0]) + 1);
	rgb[2] = ft_atoi(line + 2 + ft_intlen(rgb[0]) + 1 + ft_intlen(rgb[1]) + 1);
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
	return (!data->no_path || !data->so_path
		|| !data->we_path || !data->ea_path);
}
