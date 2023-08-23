/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:04:52 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/23 16:55:04 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data_mlx *data_mlx)
{
	int		y;
	int		x;

	y = (int)(data_mlx->persona->pos_y + data_mlx->persona->dir_y * MOVESPEED);
	x = (int)data_mlx->persona->pos_x;
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_y += data_mlx->persona->dir_y * MOVESPEED;
	y = (int)data_mlx->persona->pos_y;
	x = (int)(data_mlx->persona->pos_x + data_mlx->persona->dir_x * MOVESPEED);
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_x += data_mlx->persona->dir_x * MOVESPEED;
}

void move_down(t_data_mlx *data_mlx)
{
	int		y;
	int		x;

	y = (int)(data_mlx->persona->pos_y - data_mlx->persona->dir_y * MOVESPEED);
	x = (int)data_mlx->persona->pos_x;
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_y -= data_mlx->persona->dir_y * MOVESPEED;
	y = (int)data_mlx->persona->pos_y;
	x = (int)(data_mlx->persona->pos_x - data_mlx->persona->dir_x * MOVESPEED);
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_x -= data_mlx->persona->dir_x * MOVESPEED;
}

void	move_right(t_data_mlx *data_mlx)
{
	int		y;
	int		x;

	y = (int)(data_mlx->persona->pos_y + \
		data_mlx->persona->plane_y * MOVESPEED);
	x = (int)data_mlx->persona->pos_x;
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_y += data_mlx->persona->plane_y * MOVESPEED;
	y = (int)data_mlx->persona->pos_y;
	x = (int)(data_mlx->persona->pos_x + \
		data_mlx->persona->plane_x * MOVESPEED);
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_x += data_mlx->persona->plane_x * MOVESPEED;
}

void	move_left(t_data_mlx *data_mlx)
{
	int		y;
	int		x;

	y = (int)(data_mlx->persona->pos_y - \
		data_mlx->persona->plane_y * MOVESPEED);
	x = (int)data_mlx->persona->pos_x;
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_y -= data_mlx->persona->plane_y * MOVESPEED;
	y = (int)data_mlx->persona->pos_y;
	x = (int)(data_mlx->persona->pos_x - \
		data_mlx->persona->plane_x * MOVESPEED);
	if (data_mlx->context->map[y][x] != '1')
		data_mlx->persona->pos_x -= data_mlx->persona->plane_x * MOVESPEED;
}
