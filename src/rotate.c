/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:55:21 by aboulest          #+#    #+#             */
/*   Updated: 2023/08/23 16:56:42 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_right(t_persona *perso)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = perso->dir_x;
	perso->dir_x = perso->dir_x * cos(ROTSPEED) - perso->dir_y * sin(ROTSPEED);
	perso->dir_y = old_dir_x * sin(ROTSPEED) + perso->dir_y * cos(ROTSPEED);
	old_plane_x = perso->plane_x;
	perso->plane_x = perso->plane_x * cos(ROTSPEED) - \
		perso->plane_y * sin(ROTSPEED);
	perso->plane_y = old_plane_x * sin(ROTSPEED) +\
		perso->plane_y * cos(ROTSPEED);
}

static void	rotate_left(t_persona *perso)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = perso->dir_x;
	perso->dir_x = perso->dir_x * cos(-ROTSPEED) -\
		perso->dir_y * sin(-ROTSPEED);
	perso->dir_y = old_dir_x * sin(-ROTSPEED) +\
		perso->dir_y * cos(-ROTSPEED);
	old_plane_x = perso->plane_x;
	perso->plane_x = perso->plane_x * cos(-ROTSPEED) -\
		perso->plane_y * sin(-ROTSPEED);
	perso->plane_y = old_plane_x * sin(-ROTSPEED) +\
		perso->plane_y * cos(-ROTSPEED);
}

void	rotate(t_persona *perso, bool flag)
{

	if (flag)
		rotate_right(perso);
	else
		rotate_left(perso);
}