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

/* Straight-ahead only for now — no camera-plane spread yet (Stage 6). */
static void	init_ray(t_game *game, t_ray *ray)
{
	ray->dir_x = game->player.dir_x;
	ray->dir_y = game->player.dir_y;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	set_step(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - game->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - game->player.y) * ray->delta_dist_y;
	}
}

static void	run_dda(t_game *game, t_ray *ray)
{
	while (1)
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
		if (is_wall(game, ray->map_x, ray->map_y))
			break ;
	}
	/* raw hit distance — NOT perpendicular-corrected yet, see Stage 5 */
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist_x;
	else
		ray->perp_dist = ray->side_dist_y;
}

void	cast_ray(t_game *game, t_ray *ray)
{
	init_ray(game, ray);
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
