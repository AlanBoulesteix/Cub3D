/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:59:08 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/21 15:29:05 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int *rgb)
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
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
	data_mlx->wind = mlx_new_window(data_mlx->mlx, W_WIDTH, W_HEIGHT, W_TITLE);
	if (data_mlx->wind == 0)
		return (destroy_data_mlx(data_mlx), ERROR_MLX);
	data_mlx->imgptr = malloc(sizeof(t_img));
	if (!data_mlx->imgptr)
		return (destroy_data_mlx(data_mlx), ERROR_MLX);
	data_mlx->imgptr->img = mlx_new_image(data_mlx->mlx, W_WIDTH, W_HEIGHT);
	if (!data_mlx->imgptr->img)
		return (destroy_data_mlx(data_mlx), ERROR_MLX);
	data_mlx->imgptr->addr = mlx_get_data_addr(data_mlx->imgptr->img, \
	&data_mlx->imgptr->bits_per_pixel, \
	&data_mlx->imgptr->line_length, &data_mlx->imgptr->endian);
	data_mlx->rgb_floor = get_rgb(data->rgb_floor);
	data_mlx->rgb_ceiling = get_rgb(data->rgb_ceiling);
	return (0);
}

int	start_mlx(t_data_mlx *data_mlx, t_data *data)
{
	start_data_mlx(data_mlx, data);
	if (init_data_mlx(data_mlx, data))
		return (1);
	return (0);
}

void	destroy_data_mlx(t_data_mlx *data_mlx)
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
