/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:59:08 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/27 15:48:56 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int *rgb);

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

static void	init_raycaster_values(t_game *game)
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

int	init_game(t_game *game, t_data *data)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (free(game), printf_error(ERROR_MLX));
	game->wind = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, W_TITLE);
	if (game->wind == 0)
		return (destroy_game(game), printf_error(ERROR_MLX));
	game->imgptr = malloc(sizeof(t_img));
	if (!game->imgptr)
		return (destroy_game(game), printf_error(ERROR_MLX));
	game->imgptr->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->imgptr->img)
		return (destroy_game(game), printf_error(ERROR_MLX));
	game->imgptr->addr = mlx_get_data_addr(game->imgptr->img, \
	&game->imgptr->bits_per_pixel, \
	&game->imgptr->line_length, &game->imgptr->endian);
	if (set_textures(game, data))
		return (destroy_game(game), printf_error(ERROR_TEXT));
	if (set_persona(game, data))
		return (destroy_game(game), printf_error(ERROR_MALLOC));
	if (set_raycaster(game))
		return (destroy_game(game), printf_error(ERROR_MALLOC));
	game->rgb_floor = get_rgb(data->rgb_floor);
	game->rgb_ceiling = get_rgb(data->rgb_ceiling);
	return (0);
}
