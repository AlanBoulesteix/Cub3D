/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/23 16:56:50 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	render_img(t_data_mlx *data_mlx)
{
	raycasting(data_mlx);
	mlx_put_image_to_window(data_mlx->mlx, data_mlx->wind, data_mlx->imgptr->img, 0, 0);
}

int	loop_game(void *data)
{
	t_data_mlx	*data_mlx;
	t_persona	*perso;

	data_mlx = (t_data_mlx *)data;
	perso = data_mlx->persona;
	if (data_mlx->key_tab[_LEFT])
		rotate(perso, true);
	if (data_mlx->key_tab[_RIGHT])
		rotate(perso, false);
	if (data_mlx->key_tab[_W])
		move_up(data_mlx);
	if (data_mlx->key_tab[_S])
		move_down(data_mlx);
	if (data_mlx->key_tab[_D])
		move_right(data_mlx);
	if (data_mlx->key_tab[_A])
		move_left(data_mlx);
	render_img(data_mlx);
	return (0);
}

int	game(t_data *data)
{
	t_data_mlx	*data_mlx;

	data_mlx = malloc(sizeof(t_data_mlx));
	if (!data_mlx)
		return (1);
	if (start_mlx(data_mlx, data))
		return (1);
	set_hook(data_mlx);
	render_img(data_mlx);
	mlx_loop_hook(data_mlx->mlx, loop_game, data_mlx);
	mlx_loop(data_mlx->mlx);
	destroy_data_mlx(data_mlx);
	return (0);
}