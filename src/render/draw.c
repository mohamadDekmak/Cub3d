#include "cub3d.h"

static int	pick_color(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (get_rgb(220, 220, 60));
		return (get_rgb(60, 60, 220));
	}
	if (ray->step_y > 0)
		return (get_rgb(220, 60, 60));
	return (get_rgb(60, 220, 60));
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	wall_color;

	wall_color = pick_color(ray);
	y = 0;
	while (y < WIN_H)
	{
		if (y < ray->draw_start)
			my_pixel_put(&game->frame, x, y, game->map.ce_color);
		else if (y > ray->draw_end)
			my_pixel_put(&game->frame, x, y, game->map.fl_color);
		else
			my_pixel_put(&game->frame, x, y, wall_color);
		y++;
	}
}

void	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_W)
	{
		cast_ray(game, &ray, x);
		draw_column(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

int	render_loop(t_game *game)
{
	handle_movement(game);
	render_frame(game);
	return (0);
}
