/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:36:04 by chmadran          #+#    #+#             */
/*   Updated: 2023/09/05 11:36:50 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(char *line)
{
	if (line && (line[0] == '1' || line[0] == ' ' || line[0] == '0'
			|| line[0] == '\n'))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	ft_longest_len_tab(char **map)
{
	int		i;
	int		temp_len;
	int		longest_len;

	i = -1;
	longest_len = 0;
	temp_len = 0;
	while (map[++i])
	{
		temp_len = ft_strlen(map[i]);
		if (temp_len > longest_len)
			longest_len = temp_len;
	}
	return (longest_len);
}
