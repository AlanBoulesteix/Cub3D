/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:16:24 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/05 16:51:16 by chmadran         ###   ########.fr       */
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
	data->no_tex_path = NULL;
	data->so_tex_path = NULL;
	data->we_tex_path = NULL;
	data->ea_tex_path = NULL;
	data->rgb_floor = NULL;
	data->rgb_ceiling = NULL;
	return (data);
}

void	free_data(t_data *data)
{
	if (data->no_tex_path)
		free(data->no_tex_path);
	if (data->so_tex_path)
		free(data->so_tex_path);
	if (data->we_tex_path)
		free(data->we_tex_path);
	if (data->ea_tex_path)
		free(data->ea_tex_path);
	if (data->rgb_floor)
		free(data->rgb_floor);
	if (data->rgb_ceiling)
		free(data->rgb_ceiling);
	if (data->map)
		free_db_tab(data->map);
	free(data);
}

// void	print_data(t_data *data)
// {
// 	int	i;

// 	printf("NO : %s\n", data->no_tex_path);
// 	printf("SO : %s\n", data->so_tex_path);
// 	printf("WE : %s\n", data->we_tex_path);
// 	printf("EA : %s\n", data->ea_tex_path);
// 	printf("F : [%d:%d:%d]\n", data->rgb_floor[0],
// 		data->rgb_floor[1], data->rgb_floor[2]);
// 	printf("C : [%d:%d:%d]\n", data->rgb_ceiling[0],
// 		data->rgb_ceiling[1], data->rgb_ceiling[2]);
// 	i = -1;
// 	while (data->map[++i])
// 		printf("%s\n", data->map[i]);
// }

// void	print_map(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (map[++i])
// 	{
// 		j = -1;
// 		while (map[i][++j])
// 		{
// 			if (map[i][j] == ' ')
// 				printf("S");
// 			else if (map[i][j])
// 				printf("%c", map[i][j]);
// 		}
// 		printf("\n");
// 	}
// }
