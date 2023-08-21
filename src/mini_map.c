/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:13:06 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/21 15:29:23 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*MINI MAP A METTRE A L'ECHELLE SI ON L'UTILISE*/

void	draw_background(t_data_mlx *data_mlx, int start_x, int start_y, char bloc)
{
	int	temp_x;
	int	temp_y;

	temp_x = start_x;
	while (temp_x < start_x + 64)
	{
		temp_y = start_y;
		while (temp_y < start_y + 64)
		{
			if (temp_y % 64 == 0)
				my_mlx_pixel_put(data_mlx->imgptr, temp_y, temp_x, 0x00CCCCCC);
			else if (temp_x % 64 == 0)
				my_mlx_pixel_put(data_mlx->imgptr, temp_y, temp_x, 0x00CCCCCC);
			else if (bloc == '1')
				my_mlx_pixel_put(data_mlx->imgptr, temp_y, temp_x, 0x00000000);
			else
				my_mlx_pixel_put(data_mlx->imgptr, temp_y, temp_x, 0x00FFFFFF);
			temp_y++;
		}
		temp_x++;
	}
}

void	draw_map(t_data_mlx *data_mlx, t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			draw_background(data_mlx, x * 64, y * 64, data->map[x][y]);
			y++;
		}
		x++;
	}
}

void	draw_cam(t_data_mlx *data_mlx, t_data *data)
{
	double	i;
	double	j;
	double	ray;

	ray = data->angle - atan(0.66/1.0);
	while (ray >= data->angle - atan(0.66/1.0) && ray <= data->angle + atan(0.66/1.0))
	{

		i = data->char_pos_x;
		j = data->char_pos_y;
		while (i != data->char_pos_x + W_WIDTH && \
		j != data->char_pos_y + W_HEIGHT)
		{
			if (data->map[(int)j / 64][(int)i / 64] == '1')
				break ;
			my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00FF00FF);
			i += cos(ray);
			j += sin(ray);
		}
		ray += atan(0.66/1.0) / W_WIDTH;
	}
}

void	draw_character(t_data_mlx *data_mlx, t_data *data)
{
	int i;
	int j;

	i = data->char_pos_x - 9;
	while (++i < data->char_pos_x + 8)
	{
		j = data->char_pos_y - 9;
		while (++j < data->char_pos_y + 8)
			my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00008000);
	}
	draw_cam(data_mlx, data);
}

void	render_minimap(t_data_mlx *data_mlx, t_data *data)
{
	draw_map(data_mlx, data);
	draw_character(data_mlx, data);
	mlx_put_image_to_window(data_mlx->mlx, data_mlx->wind, data_mlx->imgptr->img, 0, 0);
}