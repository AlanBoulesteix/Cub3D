/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:49:56 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/21 18:42:19 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	keypress_handler(int keycode, void *data)
{
	t_data_mlx	*data_mlx;

	data_mlx = (t_data_mlx *)data;
	if (keycode == KEY_W)
		data_mlx->key_tab[_W] = true;
	else if (keycode == KEY_A)
		data_mlx->key_tab[_A] = true;
	else if (keycode == KEY_D)
		data_mlx->key_tab[_D] = true;
	else if (keycode == KEY_S)
		data_mlx->key_tab[_S] = true;
	else if (keycode == KEY_ESCAPE)
		mlx_loop_end(data_mlx->mlx);
	return (0);
}

static int	keyrelease_handler(int keycode, void *data)
{
	t_data_mlx	*data_mlx;

	data_mlx = (t_data_mlx *)data;
	if (keycode == KEY_W)
		data_mlx->key_tab[_W] = false;
	else if (keycode == KEY_A)
		data_mlx->key_tab[_A] = false;
	else if (keycode == KEY_D)
		data_mlx->key_tab[_D] = false;
	else if (keycode == KEY_S)
		data_mlx->key_tab[_S] = false;
	else if (keycode == KEY_ESCAPE)
		mlx_loop_end(data_mlx->mlx);
	return (0);
}

void	set_hook(t_data_mlx *data_mlx)
{
	mlx_hook(data_mlx->wind, 17, 0, mlx_loop_end, data_mlx->mlx);
	mlx_hook(data_mlx->wind, 2, (1L << 0), &keypress_handler, data_mlx);
	mlx_hook(data_mlx->wind, 3, (1L << 1), &keyrelease_handler, data_mlx);
}
