/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:59:08 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/27 15:23:04 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	set_dir_textures(t_game *game, t_data *data, int dir)
{
	char	*path;

	path = NULL;
	if (dir == NORTH)
		path = data->no_tex_path;
	else if (dir == SOUTH)
		path = data->so_tex_path;
	else if (dir == WEST)
		path = data->we_tex_path;
	else if (dir == EAST)
		path = data->ea_tex_path;
	game->tex[dir].img = mlx_xpm_file_to_image(game->mlx, path, \
		&game->tex[dir].width, &game->tex[dir].height);
	if (!game->tex[dir].img)
		return (1);
	game->tex[dir].addr = mlx_get_data_addr(game->tex[dir].img, \
		&game->tex[dir].bits_per_pixel, &game->tex[dir].line_length, \
			&game->tex[dir].endian);
	return (0);
}

int	set_textures(t_game *game, t_data *data)
{
	if (set_dir_textures(game, data, NORTH))
		return (1);
	if (set_dir_textures(game, data, SOUTH))
		return (1);
	if (set_dir_textures(game, data, WEST))
		return (1);
	if (set_dir_textures(game, data, EAST))
		return (1);
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
