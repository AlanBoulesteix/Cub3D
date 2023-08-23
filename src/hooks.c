/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:49:56 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/23 17:08:03 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	keypress_handler(int keycode, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	if (keycode == KEY_W)
		game->key_tab[_W] = true;
	else if (keycode == KEY_A)
		game->key_tab[_A] = true;
	else if (keycode == KEY_D)
		game->key_tab[_D] = true;
	else if (keycode == KEY_S)
		game->key_tab[_S] = true;
	else if (keycode == KEY_LEFT)
		game->key_tab[_LEFT] = true;
	else if (keycode == KEY_RIGHT)
		game->key_tab[_RIGHT] = true;
	else if (keycode == KEY_ESCAPE)
		mlx_loop_end(game->mlx);
	return (0);
}

static int	keyrelease_handler(int keycode, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	if (keycode == KEY_W)
		game->key_tab[_W] = false;
	else if (keycode == KEY_A)
		game->key_tab[_A] = false;
	else if (keycode == KEY_D)
		game->key_tab[_D] = false;
	else if (keycode == KEY_S)
		game->key_tab[_S] = false;
	else if (keycode == KEY_LEFT)
		game->key_tab[_LEFT] = false;
	else if (keycode == KEY_RIGHT)
		game->key_tab[_RIGHT] = false;
	else if (keycode == KEY_ESCAPE)
		mlx_loop_end(game->mlx);
	return (0);
}

void	set_hook(t_game *game)
{
	mlx_hook(game->wind, 17, 0, mlx_loop_end, game->mlx);
	mlx_hook(game->wind, 2, (1L << 0), &keypress_handler, game);
	mlx_hook(game->wind, 3, (1L << 1), &keyrelease_handler, game);
}
