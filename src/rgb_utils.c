/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:47:24 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/05 13:51:14 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_sep(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			count++;
	}
	return (count);
}

bool	rgb_is_valid(char *line)
{
	int		i;

	i = 1;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && \
			line[i] != ' ' && line[i] != '\n')
			return (false);
		i++;
	}
	if (count_sep(line) != 2)
		return (false);
	return (true);
}

int	ft_int_len(int nb)
{
	int		i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}
