/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:04:33 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/23 17:08:03 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_colone(t_raycaster *raycaster, t_game *game, int x)
{
	int	tmp;
	int	color;

	tmp = 0;
	while (tmp < raycaster->draw_start)
		my_mlx_pixel_put(game->imgptr, x, tmp++, game->rgb_ceiling);
	while (tmp < raycaster->draw_end)
	{
		if (game->texture == 1)
			color = RED;
		else if (game->texture == 2)
			color = BLUE;
		else if (game->texture == 3)
			color = YELLOW;
		else if (game->texture == 4)
			color = GREEN;
		my_mlx_pixel_put(game->imgptr, x, tmp, color);
		tmp++;
	}
	while (tmp < W_HEIGHT)
		my_mlx_pixel_put(game->imgptr, x, tmp++, game->rgb_floor);
}