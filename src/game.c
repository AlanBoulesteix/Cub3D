/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/14 16:59:25 by aboulest         ###   ########.fr       */
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

void	start_data_mlx(t_data_mlx *data_mlx, t_data *data)
{
	data_mlx->context = data;
	data_mlx->mlx = NULL;
	data_mlx->wind = NULL;
	data_mlx->img = NULL;
}

int	init_data_mlx(t_data_mlx *data_mlx, t_data *data)
{
		
	data_mlx->mlx = mlx_init();
	if (!data_mlx->mlx)
		return (free(data_mlx), ERROR_MLX);
	data_mlx->wind = mlx_new_window(data_mlx->mlx, 1024, 512, "cub3D"); //@TODO Change size of wind
	if (data_mlx->wind == 0)
		return (destroy_data_mlx(data_mlx),ERROR_MLX);
	data_mlx->img = mlx_new_image(data_mlx->mlx, 1024, 512);
	if(!data_mlx->img)
		return (destroy_data_mlx(data_mlx),ERROR_MLX);
	data_mlx->rgb_floor = get_rgb(data->rgb_floor);
	data_mlx->rgb_ceiling = get_rgb(data->rgb_ceiling);
	return (0);
}

void	draw_character(t_data_mlx *data_mlx, t_data *data)
{
	for (int i = data->char_pos_x; i < data->char_pos_x + 16; i++)
	{
		for (int j = data->char_pos_y; j < data->char_pos_y + 16; j++)
			mlx_pixel_put(data_mlx->mlx, data_mlx->wind, i, j, 16711935);
	}
}

int	key_hook(int keycode, t_data_mlx *data_mlx)
{
	if (keycode == KEY_W) // keycode == 65362 fleche
		data_mlx->context->char_pos_y--;
	else if (keycode == KEY_A) // keycode == 65361
		data_mlx->context->char_pos_x--;
	else if (keycode == KEY_D) // keycode == 65363
		data_mlx->context->char_pos_x++;
	else if (keycode == KEY_S) // keycode == 65364
		data_mlx->context->char_pos_y++;
	else if (keycode == KEY_ESCAPE)
		mlx_loop_end(data_mlx->mlx);
	draw_character(data_mlx, data_mlx->context);
	// printf("Keycode = %d\n", keycode);
	return (0);
}

int	game(t_data *data)
{
	t_data_mlx	*data_mlx;
	
	(void)data;
	data_mlx = malloc(sizeof(t_data_mlx));
	if (!data_mlx)
		return (1);
	start_data_mlx(data_mlx, data);
	if (init_data_mlx(data_mlx, data))
		return (1);
	mlx_key_hook(data_mlx->wind, key_hook, data_mlx);
	mlx_hook(data_mlx->wind, 17, 0, mlx_loop_end, data_mlx->mlx);
	mlx_loop(data_mlx->mlx);
	destroy_data_mlx(data_mlx);
	return (0);	
}