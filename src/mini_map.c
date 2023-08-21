/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:13:06 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/21 19:03:47 by aboulest         ###   ########.fr       */
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

void	draw_ray(t_data_mlx *data_mlx, t_data *data)
{
	int r = 0;
	int mx;
	int my;
	int dof;
	double rx;
	double ry;
	double ra;
	double xo;
	double yo;
	ra = data->angle;
	while (r < 1)
	{
		dof = 0;
		if (ra > PI)
		{
			ry = (((int)data->char_pos_y >> 6) << 6);
			rx = (data->char_pos_y - ry) * (-1 / tan(ra)) + data->char_pos_x;
			yo = -64;
			xo = -yo * (-1 / tan(ra));
		}
		if (ra < PI)
		{
			ry = (((int)data->char_pos_y >> 6) << 6) + 64;
			rx = (data->char_pos_y - ry) * (-1 / tan(ra)) + data->char_pos_x;
			yo = 64;
			xo = -yo * (-1 / tan(ra));
		}
		if (ra == 0 || ra == PI)
		{
			rx = data->char_pos_x;
			ry = data->char_pos_y;
			dof = W_HEIGHT >> 6;
		}
		while (dof < W_HEIGHT >> 6)
		{
			if (rx < 0)
				rx = 0;
			if (rx > W_WIDTH - 1)
				rx = W_WIDTH - 1;
			mx = (int) rx >> 6;
			if (ry < 0)
				ry = 0;
			if (ry > W_HEIGHT - 1)
				ry = W_HEIGHT - 1;
			my = (int) ry >> 6;
			if (data->map[my][mx] == '1')
			{
				for (int i = rx - 4; i < rx + 4; i++)
					for (int j = ry - 4; j < ry + 4; j++)
						my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00FF00FF);
				dof = W_HEIGHT >> 6;
			}
			else
			{
				for (int i = rx - 4; i < rx + 4; i++)
					for (int j = ry - 4; j < ry + 4; j++)
						my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00FF00FF);
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		r++;
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
	draw_ray(data_mlx, data);
	// draw_cam(data_mlx, data);
}

void	render_minimap(t_data_mlx *data_mlx, t_data *data)
{
	draw_map(data_mlx, data);
	draw_character(data_mlx, data);
	mlx_put_image_to_window(data_mlx->mlx, data_mlx->wind, data_mlx->imgptr->img, 0, 0);
}
