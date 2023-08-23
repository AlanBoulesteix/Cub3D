/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:47:51 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/23 17:08:03 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_plan(t_raycaster *ray, t_persona *persona, int x)
{
	ray->camera_x = 2 * x / (double)W_WIDTH - 1;
	ray->ray_dir_x = persona->dir_x + persona->plane_x * ray->camera_x;
	ray->ray_dir_y = persona->dir_y + persona->plane_y * ray->camera_x;
	ray->map_x = (int)persona->pos_x;
	ray->map_y = (int)persona->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INT_MAX;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INT_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	set_step(t_raycaster *ray, t_persona *persona)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (persona->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - persona->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (persona->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - persona->pos_y)
			* ray->delta_dist_y;
	}
}

static void	set_dist_wall_hit(t_raycaster *ray, t_game *game)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		ray->hit = (game->context->map[ray->map_y][ray->map_x] == '1');
	}
	if (!ray->side)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	set_height_wall(t_raycaster *raycaster, t_game *game)
{
	raycaster->line_height = (int)(W_HEIGHT / raycaster->perp_wall_dist);
	raycaster->draw_start = (-raycaster->line_height / 2) + (W_HEIGHT / 2);
	if (raycaster->draw_start < 0)
		raycaster->draw_start = 0;
	raycaster->draw_end = (raycaster->line_height / 2) + (W_HEIGHT / 2);
	if (raycaster->draw_end >= W_HEIGHT)
		raycaster->draw_end = W_HEIGHT - 1;
	if (raycaster->side == 0 && raycaster->ray_dir_x < 0)
		game->texture = 1;
	else if (raycaster->side == 0 && raycaster->ray_dir_x > 0)
		game->texture = 2;
	else if (raycaster->side == 1 && raycaster->ray_dir_y < 0)
		game->texture = 3;
	else if (raycaster->side == 1 && raycaster->ray_dir_y > 0)
		game->texture = 4;
}

void	raycasting(t_game *game)
{
	t_raycaster		*ray;
	t_persona		*persona;
	int				x;

	ray = game->raycaster;
	persona = game-> persona;
	x = 0;
	while (x < W_WIDTH)
	{
		set_plan(ray, game->persona, x);
		set_step(ray, game->persona);
		set_dist_wall_hit(ray, game);
		set_height_wall(ray, game);
		draw_colone(ray, game, x);
		x++;
	}
}
