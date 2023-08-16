/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:12:36 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/16 11:20:53 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	check_side_texture(char *str, int side);
int *find_rgb(char *line);

void	read_info_write_in_data(int fd, t_data *data)
{
	char	*line;
	char	*map;
	char	*tmp;

	line = "start";
	map = NULL;
	while(line)
	{
		line = get_next_line(fd);
		if (!data->no_path && check_side_texture(line, NORTH))
			data->no_path = ft_strdup(line + 2);
		else if (!data->so_path && check_side_texture(line, SOUTH))
			data->so_path = ft_strdup(line + 2);
		else if (!data->we_path && check_side_texture(line, WEST))
			data->we_path = ft_strdup(line + 2);
		else if (!data->ea_path && check_side_texture(line, EAST))
			data->ea_path = ft_strdup(line + 2);
		else if (ft_strlen(line) > 0 && line[0] == 'F' && !data->rgb_floor)
			data->rgb_floor = find_rgb(line);
		else if (ft_strlen(line) > 0 && line[0] == 'C' && !data->rgb_ceiling)
			data->rgb_ceiling = find_rgb(line);
		else if (line && (line[0] == '1' || line[0] == ' ' || line[0] == '0'))//@TODO : Fix a faire quand map entre-coupe d'une ligne
		{
			if (!map)
				map = ft_strdup(line);
			else
			{
				tmp = ft_strdup(map);
				free(map);
				map = ft_strjoin(tmp, line);
				free(tmp);
			}
		}
		free(line);
	}
	data->map = ft_split(map, '\n');
	free(map);
}

t_data	*read_file(char *str)
{
	int		fd;
	t_data	*data;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	data = init_data();
	if (!data)
	{
		close(fd);
		exit(EXIT_FAILURE);
	}
	read_info_write_in_data(fd, data);
	close(fd);

	//@TODO make it small function
	data->len_x = ft_strlen(data->map[0]);
	int i = -1;
	int	j;
	while (data->map[++i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'S')
			{
				data->char_pos_x = j * 64.0f + 32.0f;
				data->char_pos_y = i * 64.0f + 32.0f;
			}
			j++;
		}	
	}
		;
	data->len_y = i;
	return (data);
}
