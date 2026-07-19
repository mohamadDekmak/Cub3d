#include "cub3d.h"

int	is_wall(t_game *game, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= game->map.height)
		return (1);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (1);
	if (game->map.grid[map_y][map_x] == '1'
		|| game->map.grid[map_y][map_x] == ' ')
		return (1);
	return (0);
}

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_W - 1.0;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->distance_between_vertical_lines = 1e30;
	else
		ray->distance_between_vertical_lines = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->distance_between_horizontal_lines = 1e30;
	else
		ray->distance_between_horizontal_lines = fabs(1 / ray->dir_y);
}

static void	set_step(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->distance_to_next_vertical_line = (game->player.x - ray->map_x)
			* ray->distance_between_vertical_lines;
	}
	else
	{
		ray->step_x = 1;
		ray->distance_to_next_vertical_line = (ray->map_x + 1 - game->player.x)
			* ray->distance_between_vertical_lines;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->distance_to_next_horizontal_line = (game->player.y - ray->map_y)
			* ray->distance_between_horizontal_lines;
	}
	else
	{
		ray->step_y = 1;
		ray->distance_to_next_horizontal_line = (ray->map_y + 1 - game->player.y)
			* ray->distance_between_horizontal_lines;
	}
}

static void	run_dda(t_game *game, t_ray *ray)
{
	while (1)
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

void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(game, ray, x);
	set_step(game, ray);
	run_dda(game, ray);
	ray->line_height = (int)(WIN_H / ray->perp_dist);
	ray->draw_start = WIN_H / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = WIN_H / 2 + ray->line_height / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}
