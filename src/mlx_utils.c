/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:59:08 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/24 17:56:02 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	start_game(t_game *game, t_data *data)
{
	int	i;

	i = -1;
	while (++i < 6)
		game->key_tab[i] = false;
	game->context = data;
	game->mlx = NULL;
	game->wind = NULL;
	game->imgptr = NULL;
	game->persona = NULL;
	game->raycaster = NULL;
	i = -1;
	while (++i < 4)
	{
		game->tex[i].img = NULL;
		game->tex[i].addr = NULL;
	}
}

int	set_persona(t_game *game, t_data *data)
{
	game->persona = malloc(sizeof(t_persona));
	if (!game->persona)
		return (1);
	game->persona->pos_x = data->pos_x + 0.5;
	game->persona->pos_y = data->pos_y + 0.5;
	game->persona->dir_x = data->delta_x;
	game->persona->dir_y = data->delta_y;
	game->persona->plane_x = data->plane_x;
	game->persona->plane_y = data->plane_y;
	return (0);
}

void	init_raycaster_values(t_game *game)
{
	game->raycaster->camera_x = 0;
	game->raycaster->ray_dir_x = 0;
	game->raycaster->ray_dir_y = 0;
	game->raycaster->side_dist_x = 0;
	game->raycaster->side_dist_y = 0;
	game->raycaster->delta_dist_x = 0;
	game->raycaster->delta_dist_y = 0;
	game->raycaster->perp_wall_dist = 0;
	game->raycaster->map_x = 0;
	game->raycaster->map_y = 0;
	game->raycaster->step_x = 0;
	game->raycaster->step_y = 0;
	game->raycaster->hit = 0;
	game->raycaster->side = 0;
	game->raycaster->line_height = 0;
	game->raycaster->draw_start = 0;
	game->raycaster->draw_end = 0;
	game->raycaster->texture_img = 0;
	game->raycaster->wall_x = 0;
	game->raycaster->step_tex = 0;
	game->raycaster->tex_pos = 0;
	game->raycaster->tex_x = 0;
	game->raycaster->tex_y = 0;
}

int	set_raycaster(t_game *game)
{
	game->raycaster = malloc(sizeof(t_raycaster));
	if (!game->raycaster)
		return (1);
	init_raycaster_values(game);
	return (0);
}

int	set_textures(t_game *game, t_data *data)
{
	game->tex[NORTH].img = mlx_xpm_file_to_image(game->mlx, data->no_tex_path, &game->tex[NORTH].width, &game->tex[NORTH].height);
	if (!game->tex[NORTH].img)
		return (1);
	game->tex[NORTH].addr = mlx_get_data_addr(game->tex[NORTH].img, &game->tex[NORTH].bits_per_pixel, &game->tex[NORTH].line_length, &game->tex[NORTH].endian);
	game->tex[SOUTH].img = mlx_xpm_file_to_image(game->mlx, data->so_tex_path, &game->tex[SOUTH].width, &game->tex[SOUTH].height);
	if (!game->tex[SOUTH].img)
		return (1);
	game->tex[SOUTH].addr = mlx_get_data_addr(game->tex[SOUTH].img, &game->tex[SOUTH].bits_per_pixel, &game->tex[SOUTH].line_length, &game->tex[SOUTH].endian);
	game->tex[WEST].img = mlx_xpm_file_to_image(game->mlx, data->we_tex_path, &game->tex[WEST].width, &game->tex[WEST].height);
	if (!game->tex[WEST].img)
		return (1);
	game->tex[WEST].addr = mlx_get_data_addr(game->tex[WEST].img, &game->tex[WEST].bits_per_pixel, &game->tex[WEST].line_length, &game->tex[WEST].endian);
	game->tex[EAST].img = mlx_xpm_file_to_image(game->mlx, data->ea_tex_path, &game->tex[EAST].width, &game->tex[EAST].height);
	if (!game->tex[EAST].img)
		return (1);
	game->tex[EAST].addr = mlx_get_data_addr(game->tex[EAST].img, &game->tex[EAST].bits_per_pixel, &game->tex[EAST].line_length, &game->tex[EAST].endian);
	return (0);
}

int	init_game(t_game *game, t_data *data)
{

	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), ERROR_MLX);
	game->wind = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, W_TITLE);
	if (game->wind == 0)
		return (destroy_game(game), ERROR_MLX);
	game->imgptr = malloc(sizeof(t_img));
	if (!game->imgptr)
		return (destroy_game(game), ERROR_MLX);
	game->imgptr->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->imgptr->img)
		return (destroy_game(game), ERROR_MLX);
	game->imgptr->addr = mlx_get_data_addr(game->imgptr->img, \
	&game->imgptr->bits_per_pixel, \
	&game->imgptr->line_length, &game->imgptr->endian);
	if (set_textures(game, data))
		return (destroy_game(game), ERROR_MLX);
	if (set_persona(game, data))
		return (destroy_game(game), ERROR_MLX);
	if (set_raycaster(game))
		return (destroy_game(game), ERROR_MLX);
	game->rgb_floor = get_rgb(data->rgb_floor);
	game->rgb_ceiling = get_rgb(data->rgb_ceiling);
	return (0);
}

int	start_mlx(t_game *game, t_data *data)
{
	start_game(game, data);
	if (init_game(game, data))
		return (1);
	return (0);
}

void	destroy_game(t_game *game)
{
	int	i;

	i = -1;
	if (game->persona)
		free(game->persona);
	if (game->raycaster)
		free(game->raycaster);
	if (game->imgptr->img)
		mlx_destroy_image(game->mlx, game->imgptr->img);
	while (++i < 4)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
	}
	if (game->imgptr)
		free(game->imgptr);
	if (game->wind)
		mlx_destroy_window(game->mlx, game->wind);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}
