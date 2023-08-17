/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/17 18:11:29 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	destroy_data_mlx(t_data_mlx* data_mlx)
{
	if (data_mlx->imgptr->img)
		mlx_destroy_image(data_mlx->mlx, data_mlx->imgptr->img);
	if (data_mlx->imgptr)
		free(data_mlx->imgptr);
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
	int	i;

	i = -1;
	while (++i < 8)
		data_mlx->key_tab[i] = false;
	data_mlx->context = data;
	data_mlx->mlx = NULL;
	data_mlx->wind = NULL;
	data_mlx->imgptr = NULL;
}

int	init_data_mlx(t_data_mlx *data_mlx, t_data *data)
{

	data_mlx->mlx = mlx_init();
	if (!data_mlx->mlx)
		return (free(data_mlx), ERROR_MLX);
	data_mlx->wind = mlx_new_window(data_mlx->mlx, 1920, 1080, "cub3D");
	if (data_mlx->wind == 0)
		return (destroy_data_mlx(data_mlx),ERROR_MLX);
	data_mlx->imgptr = malloc(sizeof(t_img));
	if (!data_mlx->imgptr)
		return (destroy_data_mlx(data_mlx),ERROR_MLX);
	data_mlx->imgptr->img = mlx_new_image(data_mlx->mlx, 1920, 1080);
	if (!data_mlx->imgptr->img)
		return (destroy_data_mlx(data_mlx),ERROR_MLX);
	data_mlx->imgptr->addr = mlx_get_data_addr(data_mlx->imgptr->img, &data_mlx->imgptr->bits_per_pixel, &data_mlx->imgptr->line_length, &data_mlx->imgptr->endian);
	data_mlx->rgb_floor = get_rgb(data->rgb_floor);
	data_mlx->rgb_ceiling = get_rgb(data->rgb_ceiling);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
	float	i;
	float	j;
	int		id_i;
	int		id_j;

	i = data->char_pos_x;
	j = data->char_pos_y;
	id_i = i / 64;
	id_j = j / 64;
	while (i != data->char_pos_x + 1920 && j != data->char_pos_y + 1080)
	{
		if (data->map[(int)j / 64][(int)i / 64] == '1') //
			break ;
		my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00FF00FF);
		i += cos(data->angle + PI / 6);
		j += sin(data->angle + PI / 6);
	}
	i = data->char_pos_x;
	j = data->char_pos_y;
	id_i = i / 64;
	id_j = j / 64;
	while (i != data->char_pos_x + 1920 && j != data->char_pos_y + 1080)
	{
		if (data->map[(int)j / 64][(int)i / 64] == '1')
			break ;
		my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00FF00FF);
		i += cos(data->angle - PI / 6);
		j += sin(data->angle - PI / 6);
	}
	i = data->char_pos_x;
	j = data->char_pos_y;
	id_i = i / 64;
	id_j = j / 64;
	while (i != data->char_pos_x + 1920 && j != data->char_pos_y + 1080)
	{
		if (data->map[(int)j / 64][(int)i / 64] == '1')
			break ;
		my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00FF00FF);
		i += cos(data->angle);
		j += sin(data->angle);
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

void	draw_line(t_data_mlx *data_mlx, t_data *data)
{
	int	x;
	int	y;
	int	id_x;
	int	id_y;


	x = data->char_pos_x;
	y = data->char_pos_y;
	id_x = x / 64;
	id_y = y / 64;
	while (x < 1920)
	{
		if (x % 64 == 0)
			id_x++;
		if (y % 64 == 0)
			id_y++;
		if (data->map[id_y][id_x] == '1')
			break ;
		else
			my_mlx_pixel_put(data_mlx->imgptr, x, y, 0X00FF1515);
		x++;
	}
}

void	render_img(t_data_mlx *data_mlx, t_data *data)
{
	draw_map(data_mlx, data);
	draw_character(data_mlx, data);
	// draw_line(data_mlx, data);
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
		data_mlx->context->char_pos_x += data_mlx->context->delta_x;
		data_mlx->context->char_pos_y += data_mlx->context->delta_y;
		render_img(data_mlx, data_mlx->context);
	}
	if (data_mlx->key_tab[_S])
	{
		data_mlx->context->char_pos_x -= data_mlx->context->delta_x;
		data_mlx->context->char_pos_y -= data_mlx->context->delta_y;
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
	start_data_mlx(data_mlx, data);
	if (init_data_mlx(data_mlx, data))
		return (1);
	set_hook(data_mlx);
	render_img(data_mlx, data_mlx->context);
	mlx_loop_hook(data_mlx->mlx, loop_game, data_mlx);
	mlx_loop(data_mlx->mlx);
	destroy_data_mlx(data_mlx);
	return (0);	
}