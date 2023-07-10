/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:18:53 by aboulest          #+#    #+#             */
/*   Updated: 2022/12/01 13:07:43 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int fd, char *str)
{
	char	*buffer;
	int		count;

	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	count = 1;
	while (count > 0 && !ft_strchr(str, '\n'))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[count] = '\0';
		if (!str)
			str = ft_strdup(buffer);
		else
			str = ft_strjoin_gnl(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_before(char *str)
{
	char	*dup;
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	if (!(*str))
		return (NULL);
	while (str[nb] && str[nb] != '\n')
		nb++;
	if (str[nb] == '\n')
		nb++;
	dup = malloc(sizeof(*dup) * (nb + 1));
	if (!dup)
		return (NULL);
	while (i < nb)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*get_after(char *str)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(str[i]))
	{
		free(str);
		return (NULL);
	}
	i++;
	dup = malloc(sizeof(*dup) * (ft_strlen(str) -i + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		dup[j] = str[i + j];
		j++;
	}
	dup[j] = '\0';
	free(str);
	return (dup);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = get_line(fd, stash);
	if (!stash)
		return (NULL);
	line = get_before(stash);
	stash = get_after(stash);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("Line : %s", line);
		free(line);
	}
	return (0);
*/
