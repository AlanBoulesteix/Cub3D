/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/13 15:42:15 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	init_data_mlx(t_data_mlx *data_mlx, t_data *data)
{
	(void)data;
	
	data_mlx->mlx = mlx_init();
	if (!data_mlx->mlx)
		return (free(data_mlx), ERROR_MLX);
	data_mlx->wind = mlx_new_window(data_mlx->mlx, 1536, 1024, "cub3D");
	if (data_mlx->wind == 0)
		return(ERROR_MLX);//@TODO: free struct data
	data_mlx->img = mlx_new_image(data_mlx->mlx, 1536, 1024);
	if(!data_mlx->img)
		return(ERROR_MLX);//@TODO: free struct data
	// data_mlx->rgb_floor = get_rgb(data->rgb_floor);
	// data_mlx->rgb_ceiling = get_rgb(data->rgb_ceiling);
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
	if (init_data_mlx(data_mlx, data))
		return (1);
	// mlx_key_hook(data_mlx->wind, key_hook, vars);
	mlx_hook(data_mlx->wind, 17, 0, mlx_loop_end, data_mlx->mlx);
	mlx_loop(data_mlx->mlx);
	return (0);	
}