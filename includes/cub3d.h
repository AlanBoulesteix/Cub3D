/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:28:01 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/21 19:02:08 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h> 
# include <sys/types.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define PI	3.1451926535

# define ERROR_ARG 1
# define ERROR_EXTENSION 2

# define ERROR_RGB 1
# define ERROR_MAP 3

# define ERROR_MLX 1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define ERROR 4

# define KEY_W 119
# define KEY_A 97
# define KEY_D 100
# define KEY_S 115
# define KEY_ESCAPE 65307

# define _W 0
# define _A 1
# define _D 2
# define _S 3

# define NORTH_S 3 * PI / 2
# define SOUTH_S PI / 2
# define EAST_S 2 * PI
# define WEST_S PI

# define W_WIDTH 1920
# define W_HEIGHT 1080
# define W_TITLE "Cub3D"

typedef struct s_data
{
	char		**map;
	int			*rgb_floor;
	int			*rgb_ceiling;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	double		char_pos_x;
	double		char_pos_y;
	double		delta_x;
	double		delta_y;
	double		angle;
	char		char_side;

}				t_data;

typedef struct s_img 
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_img;

typedef struct s_data_mlx
{
	t_data		*context;
	t_img		*imgptr;
	void		*mlx;
	void		*wind;
	bool		key_tab[8];
	int			rgb_floor;
	int			rgb_ceiling;

}				t_data_mlx;

/*PARSING*/
/*#####################################################*/
/// @brief Check if arguments are valid
/// @param ac Number of arguments sent 
/// @param av list of arguments sent
/// @return 0, 1 or 2
int			check_input(int ac, char **av);

/// @brief Check if params of struct data are valid
/// @param data Struct data
/// @return 
int			check_data(t_data *data);
/*#####################################################*/

/*READ_FILE*/
/*#####################################################*/
/// @brief Read the file and write the data in a struct
/// @param str Path of the file
/// @return t_data*
t_data		*read_file(char *str);
/*#####################################################*/

/*DATA*/
/*#####################################################*/
/// @brief Init struct data
/// @return t_data*
t_data		*init_data(void);

/// @brief Free struct data
/// @param data Struct data
void		free_data(t_data *data);

/// @brief free struct data
/// @param data pointer to struct data
void		print_data(t_data *data);
/*#####################################################*/

/*DATA MLX*/
/*#####################################################*/
/// @brief Init struct data_mlx
/// @param data_mlx pointer to struct data_mlx
int			start_mlx(t_data_mlx *data_mlx, t_data *data);

/// @brief free struct data_mlx
/// @param data_mlx pointer to struct data_mlx
void		destroy_data_mlx(t_data_mlx* data_mlx);
/*#####################################################*/

/*UTILS*/
/*#####################################################*/
/// @brief free char **tab
/// @param tab pointer to pointer of char
void		free_db_tab(char **tab);
/*#####################################################*/

/*HOOKS*/
/*#####################################################*/
/// @brief Set hooks
/// @param data_mlx Struct data_mlx
void		set_hook(t_data_mlx *data_mlx);
/*#####################################################*/

/*DRAW*/
/*#####################################################*/
/// @brief Draw background
///	@param data_mlx Struct data_mlx
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
/*#####################################################*/

/*GAME*/
/*#####################################################*/
int			game(t_data *data);
/*#####################################################*/

#endif