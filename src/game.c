/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/27 14:58:39 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_img(t_game *game)
{
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->wind, game->imgptr->img, 0, 0);
}

int	loop_game(void *data)
{
	t_game		*game;
	t_persona	*perso;

	game = (t_game *)data;
	perso = game->persona;
	if (game->key_tab[_RIGHT])
		rotate(perso, true);
	if (game->key_tab[_LEFT])
		rotate(perso, false);
	if (game->key_tab[_W])
		move_up(game);
	if (game->key_tab[_S])
		move_down(game);
	if (game->key_tab[_D])
		move_right(game);
	if (game->key_tab[_A])
		move_left(game);
	render_img(game);
	return (0);
}

int	game(t_data *data)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	if (start_mlx(game, data))
		return (1);
	set_hook(game);
	render_img(game);
	mlx_loop_hook(game->mlx, loop_game, game);
	mlx_loop(game->mlx);
	destroy_game(game);
	return (0);
}
