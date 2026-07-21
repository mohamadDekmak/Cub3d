/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 00:00:00 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-21 00:00:00 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_dda(t_ray *ray)
{
	if (ray->distance_to_next_vertical_line
		< ray->distance_to_next_horizontal_line)
	{
		ray->distance_to_next_vertical_line
			+= ray->distance_between_vertical_lines;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->distance_to_next_horizontal_line
			+= ray->distance_between_horizontal_lines;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	run_dda(t_game *game, t_ray *ray)
{
	while (1)
	{
		step_dda(ray);
		if (is_wall(game, ray->map_x, ray->map_y))
			break ;
	}
	if (ray->side == 0)
		ray->perp_dist = ray->distance_to_next_vertical_line
			- ray->distance_between_vertical_lines;
	else
		ray->perp_dist = ray->distance_to_next_horizontal_line
			- ray->distance_between_horizontal_lines;
}

void	compute_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
