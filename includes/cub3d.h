/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:28:01 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/12 16:23:38 by aboulest         ###   ########.fr       */
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

# define ERROR_RGB 1
# define ERROR_MAP 3

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define ERROR 4

typedef struct s_data
{
	char		**map;
	int			*rgb_floor;
	int			*rgb_ceiling;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

}				t_data;

/*PARSING*/
/// @brief Check if arguments are valid
/// @param ac Number of arguments sent 
/// @param av list of arguments sent
/// @return 0, 1 or 2
int			check_input(int ac, char **av);
/// @brief Check if params of struct data are valid
/// @param data Struct data
/// @return 
int			check_data(t_data *data);

/*READ_FILE*/
/// @brief Read the file and write the data in a struct
/// @param str Path of the file
/// @return t_data*
t_data		*read_file(char *str);

/*DATA*/
/// @brief Init struct data
/// @return t_data*
t_data		*init_data(void);
/// @brief Free struct data
/// @param data Struct data
void		free_data(t_data *data);
/// @brief free struct data
/// @param data pointer to struct data
void		print_data(t_data *data);

/*UTILS*/
/// @brief free char **tab
/// @param tab pointer to pointer of char
void		free_db_tab(char **tab);

#endif