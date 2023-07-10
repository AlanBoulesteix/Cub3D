/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:28:01 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/10 12:43:24 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>

# define ERROR_ARG 1
# define ERROR_EXTENSION 2
# define ERROR_MAP 3

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define ERROR 4

typedef struct s_data
{
	char		**map;
	int			*color_floor;
	int			*color_ceiling;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

}				t_data;

int 	read_file(char *str);

#endif