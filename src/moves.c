/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:04:52 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/27 14:56:41 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game)
{
	int		y;
	int		x;

	y = (int)(game->persona->pos_y + game->persona->dir_y * MOVESPEED);
	x = (int)game->persona->pos_x;
	if (game->context->map[y][x] != '1')
		game->persona->pos_y += game->persona->dir_y * MOVESPEED;
	y = (int)game->persona->pos_y;
	x = (int)(game->persona->pos_x + game->persona->dir_x * MOVESPEED);
	if (game->context->map[y][x] != '1')
		game->persona->pos_x += game->persona->dir_x * MOVESPEED;
}

void	move_down(t_game *game)
{
	int		y;
	int		x;

	y = (int)(game->persona->pos_y - game->persona->dir_y * MOVESPEED);
	x = (int)game->persona->pos_x;
	if (game->context->map[y][x] != '1')
		game->persona->pos_y -= game->persona->dir_y * MOVESPEED;
	y = (int)game->persona->pos_y;
	x = (int)(game->persona->pos_x - game->persona->dir_x * MOVESPEED);
	if (game->context->map[y][x] != '1')
		game->persona->pos_x -= game->persona->dir_x * MOVESPEED;
}

void	move_right(t_game *game)
{
	int		y;
	int		x;

	y = (int)(game->persona->pos_y + \
		game->persona->plane_y * MOVESPEED);
	x = (int)game->persona->pos_x;
	if (game->context->map[y][x] != '1')
		game->persona->pos_y += game->persona->plane_y * MOVESPEED;
	y = (int)game->persona->pos_y;
	x = (int)(game->persona->pos_x + \
		game->persona->plane_x * MOVESPEED);
	if (game->context->map[y][x] != '1')
		game->persona->pos_x += game->persona->plane_x * MOVESPEED;
}

void	move_left(t_game *game)
{
	int		y;
	int		x;

	y = (int)(game->persona->pos_y - \
		game->persona->plane_y * MOVESPEED);
	x = (int)game->persona->pos_x;
	if (game->context->map[y][x] != '1')
		game->persona->pos_y -= game->persona->plane_y * MOVESPEED;
	y = (int)game->persona->pos_y;
	x = (int)(game->persona->pos_x - \
		game->persona->plane_x * MOVESPEED);
	if (game->context->map[y][x] != '1')
		game->persona->pos_x -= game->persona->plane_x * MOVESPEED;
}
