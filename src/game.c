/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/11 13:46:21 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	destroy_data_mlx(t_data_mlx * data_mlx)
{
	if (data_mlx->img)
		mlx_destroy_image(data_mlx->mlx, data_mlx->img);
	if (data_mlx->wind)
		mlx_destroy_window(data_mlx->mlx, data_mlx->wind);
	if (data_mlx->mlx)
	{
		mlx_destroy_display(data_mlx->mlx);
		free(data_mlx->mlx);
	}
	free(data_mlx);
}

void	start_data_mlx(t_data_mlx *data_mlx)
{
	data_mlx->mlx = NULL;
	data_mlx->wind = NULL;
	data_mlx->img = NULL;
}

#define START_X 0
#define START_Y 0

int	init_data_mlx(t_data_mlx *data_mlx, t_data *data)
{
	(void)data;
	
	data_mlx->mlx = mlx_init();
	if (!data_mlx->mlx)
		return (free(data_mlx), ERROR_MLX);
	data_mlx->wind = mlx_new_window(data_mlx->mlx, 1024, 512, "cub3D");
	if (data_mlx->wind == 0)
		return (destroy_data_mlx(data_mlx),ERROR_MLX);
	data_mlx->img = mlx_new_image(data_mlx->mlx, 1024, 512);
	if(!data_mlx->img)
		return (destroy_data_mlx(data_mlx),ERROR_MLX);
	for (int x=START_X; x < START_X + 1024; x++)
	{
		for (int y = START_Y; y < START_Y + 512; y++)
		{
			mlx_pixel_put(data_mlx->mlx, data_mlx->wind, x, y, 155);
		}
	}
	data_mlx->rgb_floor = get_rgb(data->rgb_floor);
	data_mlx->rgb_ceiling = get_rgb(data->rgb_ceiling);
	return (0);
}

int	key_hook(int keycode, t_data_mlx *data_mlx)
{
	(void)data_mlx;
	(void)keycode;
	return (0);
}

int	game(t_data *data)
{
	t_data_mlx	*data_mlx;
	
	(void)data;
	data_mlx = malloc(sizeof(t_data_mlx));
	if (!data_mlx)
		return (1);
	start_data_mlx(data_mlx);
	if (init_data_mlx(data_mlx, data))
		return (1);
	// mlx_key_hook(data_mlx->wind, key_hook, vars);
	mlx_hook(data_mlx->wind, 17, 0, mlx_loop_end, data_mlx->mlx);
	mlx_loop(data_mlx->mlx);
	destroy_data_mlx(data_mlx);
	return (0);	
}