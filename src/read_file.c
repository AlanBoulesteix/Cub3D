/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:12:36 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/04 14:12:02 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int		check_side_texture(char *str, int side);
int		*find_rgb(char *line);

char	*write_in_map(char *map, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (!map)
		map = ft_strdup(line);
	else
	{
		tmp = ft_strdup(map);
		free(map);
		map = ft_strjoin(tmp, line);
		free(tmp);
	}
	return (map);
}

void	write_in_data(char *map, t_data *data)
{
	data->map = ft_split(map, '\n');
	free(map);
	data->no_tex_path[ft_strlen(data->no_tex_path) - 1] = '\0';
	data->so_tex_path[ft_strlen(data->so_tex_path) - 1] = '\0';
	data->ea_tex_path[ft_strlen(data->ea_tex_path) - 1] = '\0';
	data->we_tex_path[ft_strlen(data->we_tex_path) - 1] = '\0';
}

void	read_info_write_in_data(int fd, t_data *data)
{
	char	*line;
	char	*map;

	line = "start";
	map = NULL;
	while (line)
	{
		line = get_next_line(fd);
		if (!data->no_tex_path && check_side_texture(line, NORTH))
			data->no_tex_path = ft_strdup(line + 2);
		else if (!data->so_tex_path && check_side_texture(line, SOUTH))
			data->so_tex_path = ft_strdup(line + 2);
		else if (!data->we_tex_path && check_side_texture(line, WEST))
			data->we_tex_path = ft_strdup(line + 2);
		else if (!data->ea_tex_path && check_side_texture(line, EAST))
			data->ea_tex_path = ft_strdup(line + 2);
		else if (ft_strlen(line) > 0 && line[0] == 'F' && !data->rgb_floor)
			data->rgb_floor = find_rgb(line);
		else if (ft_strlen(line) > 0 && line[0] == 'C' && !data->rgb_ceiling)
			data->rgb_ceiling = find_rgb(line);
		else if (line && (line[0] == '1' || line[0] == ' ' || line[0] == '0'))
			map = write_in_map(map, line);
		free(line);
	}
	write_in_data(map, data);
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
	fill_map(data);
	return (data);
}
