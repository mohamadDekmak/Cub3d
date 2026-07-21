/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 00:00:00 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-21 00:00:00 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	pick_tex_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (WE);
		return (EA);
	}
	if (ray->step_y > 0)
		return (NO);
	return (SO);
}

static int	compute_tex_x(t_ray *ray, t_img *tex)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static void	set_tex_column(t_game *game, t_ray *ray)
{
	t_img	*tex;

	ray->tex_index = pick_tex_index(ray);
	tex = &game->tex[ray->tex_index];
	ray->tex_x = compute_tex_x(ray, tex);
	ray->tex_step = (double)tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2)
		* ray->tex_step;
}

static void	draw_tex_pixel(t_game *game, t_ray *ray, int x, int y)
{
	t_img	*tex;
	int		tex_y;

	tex = &game->tex[ray->tex_index];
	tex_y = (int)ray->tex_pos;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	my_pixel_put(&game->frame, x, y, get_tex_pixel(tex, ray->tex_x, tex_y));
	ray->tex_pos += ray->tex_step;
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	y;

	set_tex_column(game, ray);
	y = 0;
	while (y < WIN_H)
	{
		if (y < ray->draw_start)
			my_pixel_put(&game->frame, x, y, game->map.ce_color);
		else if (y > ray->draw_end)
			my_pixel_put(&game->frame, x, y, game->map.fl_color);
		else
			draw_tex_pixel(game, ray, x, y);
		y++;
	}
}
