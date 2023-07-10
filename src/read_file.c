#include "cub3d.h"
#include "get_next_line.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	data->map = NULL;
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->color_floor = NULL;
	data->color_ceiling = NULL;
	return (data);
}

int	find_side_texture(char *line)
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

int check_texture(t_data *data)
{
	return (!data->no_path || !data->so_path ||
		!data->we_path || !data->ea_path);
}

int	ft_intlen(int n)
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

void	free_db_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_data(t_data *data)
{
	if (data->no_path)
		free(data->no_path);
	if (data->so_path)
		free(data->so_path);
	if (data->we_path)
		free(data->we_path);
	if (data->ea_path)
		free(data->ea_path);
	if (data->color_floor)
		free(data->color_floor);
	if (data->color_ceiling)
		free(data->color_ceiling);	
	if (data->map)
		free_db_tab(data->map);
	free(data);
}

void	read_info(int fd, t_data *data) //@TODO: problem w/ leaks GNL when 
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
		else if (ft_strlen(line) > 0 && line[0] == 'F')
			data->color_floor = find_rgb(line);
		else if (ft_strlen(line) > 0 && line[0] == 'C')
			data->color_ceiling = find_rgb(line);
		else if (line && (line[0] == '1' || line[0] == ' ' || line[0] == '0'))
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


int read_file(char *str)
{
	int		fd;
	t_data	*data;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	data = init_data();
	read_info(fd, data);
	printf("NO : %s\n", data->no_path);
	printf("SO : %s\n", data->so_path);
	printf("WE : %s\n", data->we_path);
	printf("EA : %s\n", data->ea_path);
	printf("F : [%d:%d:%d]\n", data->color_floor[0], data->color_floor[1], data->color_floor[2]);
	printf("C : [%d:%d:%d]\n", data->color_ceiling[0], data->color_ceiling[1], data->color_ceiling[2]);
	int i = -1;
	while (data->map[++i])
		printf("%s\n", data->map[i]);
	close(fd);
	free_data(data);
	return (0);
}
