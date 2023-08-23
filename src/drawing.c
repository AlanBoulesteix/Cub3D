/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:04:33 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/23 12:05:04 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_colone(t_raycaster *raycaster, t_data_mlx *data_mlx, int x)
{
	int	tmp;
	int	color;

	tmp = 0;
	while (tmp < raycaster->draw_start)
		my_mlx_pixel_put(data_mlx->imgptr, x, tmp++, data_mlx->rgb_ceiling);
	while (tmp < raycaster->draw_end)
	{
		if (data_mlx->texture == 1)
			color = RED;
		else if (data_mlx->texture == 2)
			color = BLUE;
		else if (data_mlx->texture == 3)
			color = YELLOW;
		else if (data_mlx->texture == 4)
			color = GREEN;
		my_mlx_pixel_put(data_mlx->imgptr, x, tmp, color);
		tmp++;
	}
	while (tmp < W_HEIGHT)
		my_mlx_pixel_put(data_mlx->imgptr, x, tmp++, data_mlx->rgb_floor);
}