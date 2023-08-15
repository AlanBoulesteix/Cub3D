/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:16:24 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/15 17:47:02 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Malloc");
		return (NULL);
	}
	data->map = NULL;
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->rgb_floor = NULL;
	data->rgb_ceiling = NULL;
	return (data);
}

void	free_data(t_data *data)
{
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->we_path)
		free(data->we_path);
	if (data->ea_path)
		free(data->ea_path);
	if (data->rgb_floor)
		free(data->rgb_floor);
	if (data->rgb_ceiling)
		free(data->rgb_ceiling);
	if (data->map)
		free_db_tab(data->map);
	free(data);
}

void	print_data(t_data *data)
{
	int	i;

	printf("NO : %s\n", data->no_path);
	printf("SO : %s\n", data->so_path);
	printf("WE : %s\n", data->we_path);
	printf("EA : %s\n", data->ea_path);
	printf("F : [%d:%d:%d]\n", data->rgb_floor[0],
		data->rgb_floor[1], data->rgb_floor[2]);
	printf("C : [%d:%d:%d]\n", data->rgb_ceiling[0],
		data->rgb_ceiling[1], data->rgb_ceiling[2]);
	i = -1;
	while (data->map[++i])
		printf("%s\n", data->map[i]);
	printf("len_x = %d\tlen_y = %d\n", data->len_x, data->len_x);
	printf("coord_x_char = %f\tcoord_y_char = %f\n", data->char_pos_x, data->char_pos_y);
}
