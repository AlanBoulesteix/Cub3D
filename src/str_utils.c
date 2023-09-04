/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:09:01 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/04 18:49:43 by chmadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(char *line)
{
	char	*path;
	char	*new_path;

	path = NULL;
	path = ft_strchr(line, '.');
	if (!path)
		path = ft_strchr(line, '/');
	new_path = ft_strdup(path);
	return (new_path);
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
