/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:12:36 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/05 14:17:23 by chmadran         ###   ########.fr       */
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

int	write_in_data(char *map, t_data *data)
{
	if (check_map_empty_line(map))
		return (free(map), EXIT_FAILURE);
	data->map = ft_split(map, '\n');
	free(map);
	data->no_tex_path[ft_strlen(data->no_tex_path) - 1] = '\0';
	data->so_tex_path[ft_strlen(data->so_tex_path) - 1] = '\0';
	data->ea_tex_path[ft_strlen(data->ea_tex_path) - 1] = '\0';
	data->we_tex_path[ft_strlen(data->we_tex_path) - 1] = '\0';
	return (EXIT_SUCCESS);
}

int	read_info_write_in_data(int fd, t_data *data)
{
	char	*map;
	char	*line;

	line = "start";
	map = NULL;
	while (line)
	{
		line = get_next_line(fd);
		if (!data->no_tex_path && check_side_texture(line, NORTH))
			data->no_tex_path = get_path(line);
		else if (!data->so_tex_path && check_side_texture(line, SOUTH))
			data->so_tex_path = get_path(line);
		else if (!data->we_tex_path && check_side_texture(line, WEST))
			data->we_tex_path = get_path(line);
		else if (!data->ea_tex_path && check_side_texture(line, EAST))
			data->ea_tex_path = get_path(line);
		else if (ft_strlen(line) > 0 && line[0] == 'F' && !data->rgb_floor)
			data->rgb_floor = find_rgb(line);
		else if (ft_strlen(line) > 0 && line[0] == 'C' && !data->rgb_ceiling)
			data->rgb_ceiling = find_rgb(line);
		else if (check_map_start(data, line, map) == EXIT_SUCCESS)
			map = write_in_map(map, line);
		free(line);
	}
	return (write_in_data(map, data));
}

void	fill_map_spaces(t_data *data)
{
	int		i;
	int		j;
	char	**new_map;
	int		longest_len;

	i = -1;
	longest_len = ft_longest_len_tab(data->map);
	new_map = malloc(sizeof(char *) * (ft_tablen(data->map) + 1));
	while (data->map[++i])
	{
		new_map[i] = malloc(sizeof(char) * (longest_len + 1));
		j = -1;
		while (data->map[i][++j])
			new_map[i][j] = data->map[i][j];
		while (j < longest_len)
			new_map[i][j++] = ' ';
		new_map[i][j] = '\0';
	}
	new_map[i] = NULL;
	free_db_tab(data->map);
	data->map = new_map;
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
	if (read_info_write_in_data(fd, data))
		return (close(fd), free_data(data), NULL);
	close(fd);
	fill_map_coordinate(data);
	fill_map_spaces(data);
	return (data);
}
