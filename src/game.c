/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/21 15:32:06 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	cam(t_data_mlx *data_mlx, t_data *data)
{
	double	dir_x;
	double	dir_y;
	double	ray;

	ray = data->angle - atan(0.66/1.0);
	while (ray >= data->angle - atan(0.66/1.0) && ray <= data->angle + atan(0.66/1.0))
	{
		dir_x = data->char_pos_x;
		dir_y = data->char_pos_y;
		while (dir_x != data->char_pos_x + W_WIDTH && dir_y != data->char_pos_y + W_HEIGHT)
		{
			if (data->map[(int)dir_y / 64][(int)dir_x / 64] == '1')
				break ;
			my_mlx_pixel_put(data_mlx->imgptr, dir_x, dir_y, 0X00FF00FF);
			dir_x += cos(ray);
			dir_y += sin(ray);
		}
		ray += atan(0.66/1.0) / W_WIDTH;
	}
}

void	render_img(t_data_mlx *data_mlx, t_data *data)
{
	cam(data_mlx, data);
	mlx_put_image_to_window(data_mlx->mlx, data_mlx->wind, data_mlx->imgptr->img, 0, 0);
}

int	loop_game(void *data)
{
	t_data_mlx *data_mlx = (t_data_mlx *)data;
	
	if (data_mlx->key_tab[_A])
	{
		data_mlx->context->angle -= 0.1;
		if (data_mlx->context->angle < 0)
			data_mlx->context->angle = 2 * PI;
		data_mlx->context->delta_x = cos(data_mlx->context->angle) * 5;
		data_mlx->context->delta_y = sin(data_mlx->context->angle) * 5;
		render_img(data_mlx, data_mlx->context);
	}
	if (data_mlx->key_tab[_D])
	{
		data_mlx->context->angle += 0.1;
		if (data_mlx->context->angle > 2 * PI)
			data_mlx->context->angle = 0;
		data_mlx->context->delta_x = cos(data_mlx->context->angle) * 5;
		data_mlx->context->delta_y = sin(data_mlx->context->angle) * 5;
		render_img(data_mlx, data_mlx->context);
	}
	if (data_mlx->key_tab[_W])
	{
		//@TODO: CHANGE CODE DUE TO NORM
		int x = (int)(data_mlx->context->char_pos_x + data_mlx->context->delta_x) / 64;
		int y = (int)(data_mlx->context->char_pos_y + data_mlx->context->delta_y) / 64;
		if (data_mlx->context->map[y][x] != '1')
		{
			data_mlx->context->char_pos_x += data_mlx->context->delta_x;
			data_mlx->context->char_pos_y += data_mlx->context->delta_y;
		}
		render_img(data_mlx, data_mlx->context);
	}
	if (data_mlx->key_tab[_S])
	{
		//@TODO: CHANGE CODE DUE TO NORM
		int x = (int)(data_mlx->context->char_pos_x + data_mlx->context->delta_x) / 64;
		int y = (int)(data_mlx->context->char_pos_y + data_mlx->context->delta_y) / 64;
		if (data_mlx->context->map[y][x] != '1')
		{
			data_mlx->context->char_pos_x -= data_mlx->context->delta_x;
			data_mlx->context->char_pos_y -= data_mlx->context->delta_y;
		}
		render_img(data_mlx, data_mlx->context);
	}
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
	render_img(data_mlx, data_mlx->context);
	mlx_loop_hook(data_mlx->mlx, loop_game, data_mlx);
	mlx_loop(data_mlx->mlx);
	destroy_data_mlx(data_mlx);
	return (0);	
}