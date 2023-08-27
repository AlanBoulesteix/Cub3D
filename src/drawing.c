/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:04:33 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/27 14:53:03 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > W_HEIGHT - 1 || x < 0 || x > W_WIDTH - 1)
		return ;
	pixel = (img->addr + (y * img->line_length + x * \
		(img->bits_per_pixel / 8)));
	*(unsigned int *)pixel = color;
}

int	get_color(t_game *game, int x, int y, int i)
{
	return (*(int *)(game->tex[i].addr + (y * game->tex[i].line_length + x
			* (game->tex[i].bits_per_pixel / 8))));
}

void	init_spread(t_game *game, t_raycaster *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->persona->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->persona->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEXWIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = TEXWIDTH - ray->tex_x - 1;
	ray->step_tex = TEXHEIGHT  * 1.0 / ray->line_height;
	ray->tex_pos = (ray->draw_start - W_HEIGHT / 2 + ray->line_height / 2) * ray->step_tex;
}

void	draw_colone(t_raycaster *raycaster, t_game *game, int x)
{
	int	tmp;

	tmp = 0;
	init_spread(game, raycaster);
	while (tmp < raycaster->draw_start)
		my_mlx_pixel_put(game->imgptr, x, tmp++, game->rgb_ceiling);
	while (tmp < raycaster->draw_end)
	{
		my_mlx_pixel_put(game->imgptr, x, tmp, get_color(game, \
			raycaster->tex_x, raycaster->tex_pos, game->texture));
		raycaster->tex_pos += raycaster->step_tex;
		tmp++;
	}
	while (tmp < W_HEIGHT)
		my_mlx_pixel_put(game->imgptr, x, tmp++, game->rgb_floor);
}
