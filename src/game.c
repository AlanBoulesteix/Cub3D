/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:45:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/22 18:21:11 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_minimap(t_data_mlx *data_mlx, t_data *data);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	cam(t_data_mlx *data_mlx, t_data *data)
{
	int		x;
	int		map_x;
	int		map_y;
	int 	step_x;
	int 	step_y;
	int		hit;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double side_dist_x;
	double side_dist_y;
	bool	side;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	
	x = 0;
	while (x < W_WIDTH)
	{
		camera_x = 2 * x / (double)W_WIDTH - 1;
		ray_dir_x = data_mlx->persona->dir_x + data_mlx->persona->plane_x * camera_x;
		ray_dir_y = data_mlx->persona->dir_y + data_mlx->persona->plane_y * camera_x;
		//########################################################
		map_x = (int)data_mlx->persona->pos_x;
		map_y = (int)data_mlx->persona->pos_y;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);
		hit = 0;
		//####################Calcule Step#########################
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data_mlx->persona->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data_mlx->persona->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data_mlx->persona->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data_mlx->persona->pos_y) * delta_dist_y;
		}
		//########################################################
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			hit = (data->map[map_y][map_x] == '1');
		}
		if (!side)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		//########################################################
		int line_height;
		int draw_start;
		int draw_end;
		int	texture_img;
		
		line_height = (int)(W_HEIGHT / perp_wall_dist);
		draw_start = (-line_height / 2) + (W_HEIGHT / 2);
		if (draw_start < 0)
			draw_start = 0;
		draw_end = (line_height / 2) + (W_HEIGHT / 2);
		if (draw_end >= W_HEIGHT)
			draw_end = W_HEIGHT - 1;
		if (side == 0 && ray_dir_x < 0)
			texture_img = 1;
		else if (side == 0 && ray_dir_x > 0)
			texture_img = 2;
		else if (side == 1 && ray_dir_y < 0)
			texture_img = 3;
		else if (side == 1 && ray_dir_y > 0)
			texture_img = 4;
		//########################################################
		//Draw
		int tmp;
		int color;
		
		tmp = 0;
		while(tmp < draw_start)
			my_mlx_pixel_put(data_mlx->imgptr, x, tmp++, BLACK);
		while(tmp < draw_end)
		{
			if (texture_img == 1)
				color = RED;
			else if (texture_img == 2)
				color = BLUE;
			else if (texture_img == 3)
				color = YELLOW;
			else if (texture_img == 4)
				color = GREEN;
			my_mlx_pixel_put(data_mlx->imgptr, x, tmp, color);
			tmp++;
		}
		while(tmp < W_HEIGHT)
			my_mlx_pixel_put(data_mlx->imgptr, x, tmp++, BLACK);
		x++;
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
	int 		y;
	int 		x;
	double 		old_dir_x;
	double 		old_plane_x;

	y = 0;
	x = 0;
	if (data_mlx->key_tab[_D])
	{
		old_dir_x = data_mlx->persona->dir_x;
		data_mlx->persona->dir_x = data_mlx->persona->dir_x * cos(ROTSPEED) - data_mlx->persona->dir_y * sin(ROTSPEED);
		data_mlx->persona->dir_y = old_dir_x * sin(ROTSPEED) + data_mlx->persona->dir_y * cos(ROTSPEED);
		old_plane_x = data_mlx->persona->plane_x;
		data_mlx->persona->plane_x = data_mlx->persona->plane_x * cos(ROTSPEED) - data_mlx->persona->plane_y * sin(ROTSPEED);
		data_mlx->persona->plane_y = old_plane_x * sin(ROTSPEED) + data_mlx->persona->plane_y * cos(ROTSPEED);
	}
	if (data_mlx->key_tab[_A])
	{
		old_dir_x = data_mlx->persona->dir_x;
		data_mlx->persona->dir_x = data_mlx->persona->dir_x * cos(-ROTSPEED) - data_mlx->persona->dir_y * sin(-ROTSPEED);
		data_mlx->persona->dir_y = old_dir_x * sin(-ROTSPEED) + data_mlx->persona->dir_y * cos(-ROTSPEED);
		old_plane_x = data_mlx->persona->plane_x;
		data_mlx->persona->plane_x = data_mlx->persona->plane_x * cos(-ROTSPEED) - data_mlx->persona->plane_y * sin(-ROTSPEED);
		data_mlx->persona->plane_y = old_plane_x * sin(-ROTSPEED) + data_mlx->persona->plane_y * cos(-ROTSPEED);
	}
	if (data_mlx->key_tab[_W])
	{
		y = (int)data_mlx->persona->pos_x + data_mlx->persona->dir_x * MOVESPEED;
		x = (int)data_mlx->persona->pos_y + data_mlx->persona->dir_y * MOVESPEED;
		if (data_mlx->context->map[x][y] != 1)
		{
			data_mlx->persona->pos_x += data_mlx->persona->dir_x * MOVESPEED;
			data_mlx->persona->pos_y += data_mlx->persona->dir_y * MOVESPEED;
		}
	}
	if (data_mlx->key_tab[_S])
	{
		y = (int)data_mlx->persona->pos_x + data_mlx->persona->dir_x * MOVESPEED;
		x = (int)data_mlx->persona->pos_y + data_mlx->persona->dir_y * MOVESPEED;
		if (data_mlx->context->map[x][y] != 1)
		{
			data_mlx->persona->pos_x -= data_mlx->persona->dir_x * MOVESPEED;
			data_mlx->persona->pos_y -= data_mlx->persona->dir_y * MOVESPEED;
		}
	}
	render_img(data_mlx, data_mlx->context);
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