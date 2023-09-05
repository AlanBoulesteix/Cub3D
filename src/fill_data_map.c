/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:08:54 by chmadran          #+#    #+#             */
/*   Updated: 2023/09/05 10:52:54 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

static void	fill_delta_plane_ns(t_data *data, double x, double y)
{
	data->delta_x = 0;
	data->plane_y = 0.00;
	data->plane_x = x;
	data->delta_y = y;
}

static void	fill_delta_plane_ew(t_data *data, double x, double y)
{
	data->delta_y = 0;
	data->plane_x = 0.00;
	data->delta_x = x;
	data->plane_y = y;
}

void	fill_map_coordinate(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'S' || data->map[i][j] == 'N' ||
			data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->pos_x = j;
				data->pos_y = i;
				if (data->map[i][j] == 'N')
					fill_delta_plane_ns(data, 0.66, -1);
				else if (data->map[i][j] == 'S')
					fill_delta_plane_ns(data, -0.66, 1);
				else if (data->map[i][j] == 'E')
					fill_delta_plane_ew(data, 1, 0.66);
				else if (data->map[i][j] == 'W')
					fill_delta_plane_ew(data, -1, -0.66);
			}
		}
	}
}
