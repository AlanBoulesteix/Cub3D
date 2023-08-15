/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/15 18:21:58 by aboulest         ###   ########.fr       */
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
				my_mlx_pixel_put(data_mlx->imgptr, temp_y, temp_x, 0x00000000);
			else if (temp_x % 64 == 0)
				my_mlx_pixel_put(data_mlx->imgptr, temp_y, temp_x, 0x00000000);
			else if (bloc == '1')
				my_mlx_pixel_put(data_mlx->imgptr, temp_y, temp_x, 0x000066FF);
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

void	draw_character(t_data_mlx *data_mlx, t_data *data)
{
	for (int i = data->char_pos_x; i < data->char_pos_x + 16; i++)
	{
		for (int j = data->char_pos_y ; j < data->char_pos_y + 16; j++)
			my_mlx_pixel_put(data_mlx->imgptr, i, j, 0X00FF00FF);
	}
}

void	render_img(t_data_mlx *data_mlx, t_data *data)
{
	draw_map(data_mlx, data);
	draw_character(data_mlx, data);
	mlx_put_image_to_window(data_mlx->mlx, data_mlx->wind, data_mlx->imgptr->img, 0, 0);
	// printf("coord_x_char = %f\tcoord_y_char = %f\n", data->char_pos_x, data->char_pos_y);
}

int	loop_game(void *data)
{
	t_data_mlx *data_mlx = (t_data_mlx *)data;
	
	if (data_mlx->key_tab[_W])
	{
		data_mlx->context->char_pos_y -= 2.0f;
		render_img(data_mlx, data_mlx->context);
	}
	if (data_mlx->key_tab[_S])
	{
		data_mlx->context->char_pos_y += 2.0f;
		render_img(data_mlx, data_mlx->context);
	}
	if (data_mlx->key_tab[_A])
	{
		data_mlx->context->char_pos_x -= 2.0f;
		render_img(data_mlx, data_mlx->context);
	}
	if (data_mlx->key_tab[_D])
	{
		data_mlx->context->char_pos_x += 2.0f;
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