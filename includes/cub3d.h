/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmadran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:28:01 by aboulest          #+#    #+#             */
/*   Updated: 2023/09/05 11:38:42 by chmadran         ###   ########.fr       */
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
# include <limits.h>
# include "../minilibx-linux/mlx.h"

# define PI	3.1451926535

# define ERROR_ARG 1
# define ERROR_EXTENSION 2
# define ERROR_RGB 3
# define ERROR_MAP 4
# define ERROR_MALLOC 5
# define ERROR_MLX 6
# define ERROR_TEXT 7
# define ERROR_EMPTY_LINE 8

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
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define _W 0
# define _A 1
# define _D 2
# define _S 3
# define _LEFT 4
# define _RIGHT 5

# define W_TITLE "Cub3D"
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define MOVESPEED 0.1
# define ROTSPEED 0.1

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef struct s_data
{
	char		**map;
	int			*rgb_floor;
	int			*rgb_ceiling;
	double		pos_x;
	double		pos_y;
	double		delta_x;
	double		delta_y;
	double		plane_x;
	double		plane_y;
	char		*no_tex_path;
	char		*so_tex_path;
	char		*we_tex_path;
	char		*ea_tex_path;

}				t_data;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

}				t_img;

typedef struct s_tex
{
	void		*img;
	char		*addr;
	char		*path;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;

}				t_tex;

typedef struct s_persona
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

}				t_persona;

typedef struct s_raycaster
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	double		step_tex;
	double		tex_pos;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			texture_img;
	int			tex_x;
	int			tex_y;
}				t_raycaster;

typedef struct s_game
{
	t_data			*context;
	t_img			*imgptr;
	t_persona		*persona;
	t_raycaster		*raycaster;
	t_tex			tex[4];
	void			*mlx;
	void			*wind;
	bool			key_tab[6];
	int				rgb_floor;
	int				rgb_ceiling;
	int				texture;

}					t_game;

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

/// @brief Return 1 and write error
/// @param error Error code
/// @return 1
int			printf_error(int error);

/// @brief check if the map stored in data is correct
/// @param map Map stored in data
/// @return 0 or 1
int			check_data_map(char **map);

/// @brief counts the number of tabs/lines in a char **
/// @param map Map stored in data
/// @return 0 or 1
int			ft_tablen(char **tab);

/// @brief checks if the character sent is not a space 
/// @param character the map character to be checked
/// @return 0 or 1
int			check_character(char character);

/*#####################################################*/

/*READ_FILE*/
/*#####################################################*/
/// @brief Read the file and write the data in a struct
/// @param str Path of the file
/// @return t_data*
t_data		*read_file(char *str);

/// @brief Check if theres an empty line in the map before it gets stored
/// @param map Map as a char*
/// @return 0 or 1
int			check_map_empty_line(char *map);

/// @brief get path of texture
/// @param line line of the file
/// @return path of texture
char		*get_path(char *line);

/*#####################################################*/

/*READ_FILE_UTILS2*/
/*#####################################################*/
/// @brief Check if the line is valid
/// @param line line of the file
/// @return 0 or 1
int			check_line(char *line);

/// @brief Get the longest line of the map
/// @param map Map as a char**
/// @return length of the longest line
int			ft_longest_len_tab(char **map);

/*#####################################################*/

/*FILL_DATA_MAP*/
/*#####################################################*/
/// @brief Fill the map in the struct data
/// @param data Struct data
/// @return
void		fill_map_coordinate(t_data *data);
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
/// @brief Init struct game
/// @param game pointer to struct game
int			start_mlx(t_game *game, t_data *data);

/// @brief free struct game
/// @param game pointer to struct game
void		destroy_game(t_game *game);
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
/// @param game Struct game
void		set_hook(t_game *game);

///@brief Move up
/// @param game Struct game
void		move_up(t_game *game);

///@brief Move down
/// @param game Struct game
void		move_down(t_game *game);

///@brief Move right
/// @param game Struct game
void		move_right(t_game *game);

///@brief Move left
/// @param game Struct game
void		move_left(t_game *game);

///@brief Rotate
/// @param persona Struct persona
/// @param flag true or false
void		rotate(t_persona *persona, bool flag);
/*#####################################################*/

/*DRAW*/
/*#####################################################*/
/// @brief Draw pixel into the image
///	@param game Struct game
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);

/// @brief Draw colone into the image
/// @param raycaster Struct raycaster
///	@param game Struct game
///	@param x position x
void		draw_colone(t_raycaster *raycaster, t_game *game, int x);
/*#####################################################*/

/*GAME*/
/*#####################################################*/
int			game(t_data *data);

/// @brief raycasting
/// @param game Struct game
void		raycasting(t_game *game);

/// @brief Init struct game
/// @param game pointer to struct game
/// @param data pointer to struct data
/// @return 0 or 1
int			init_game(t_game *game, t_data *data);

/// @brief Set game values
/// @param game pointer to struct game
/// @param data pointer to struct data
void		start_game(t_game *game, t_data *data);

/// @brief Set textures
/// @param game pointer to struct game
/// @param data pointer to struct data
/// @return 0 or 1
int			set_textures(t_game *game, t_data *data);

/// @brief Set persona
/// @param game pointer to struct game
/// @param data pointer to struct data
/// @return 0 or 1
int			set_persona(t_game *game, t_data *data);

/// @brief Set raycaster
///	@param game pointer to struct game
/// @return 0 or 1
int			set_raycaster(t_game *game);
/*#####################################################*/

#endif