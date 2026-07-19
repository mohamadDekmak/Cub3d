#include "cub3d.h"

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		if (y < ray->draw_start)
			my_pixel_put(&game->frame, x, y, game->map.ce_color);
		else if (y > ray->draw_end)
			my_pixel_put(&game->frame, x, y, game->map.fl_color);
		else
			my_pixel_put(&game->frame, x, y, get_rgb(200, 200, 200));
		y++;
	}
}

static void	draw_bar(t_game *game, int x, int center_y, int height, int color)
{
	int	y;
	int	half;

	half = height / 2;
	y = center_y - half;
	while (y < center_y + half)
	{
		my_pixel_put(&game->frame, x, y, color);
		my_pixel_put(&game->frame, x + 1, y, color);
		y++;
	}
}

static void	draw_fisheye_demo(t_game *game)
{
	static const double	camera_xs[5] = {-1.0, -0.5, 0.0, 0.5, 1.0};
	static const int		xs[5] = {140, 390, 640, 890, 1140};
	double	wall_depth;
	double	euclid_dist;
	int		i;

	wall_depth = 3.0;
	i = 0;
	while (i < 5)
	{
		euclid_dist = wall_depth * sqrt(1.0 + pow(camera_xs[i]
					* game->player.plane_x, 2));
		draw_bar(game, xs[i], 200, (int)(WIN_H / euclid_dist),
			get_rgb(255, 60, 60));
		draw_bar(game, xs[i], 550, (int)(WIN_H / wall_depth),
			get_rgb(60, 255, 60));
		i++;
	}
}

void	render_frame(t_game *game)
{
	int		x;
	int		y;
	t_ray	ray;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				my_pixel_put(&game->frame, x, y, game->map.ce_color);
			else
				my_pixel_put(&game->frame, x, y, game->map.fl_color);
			x++;
		}
		y++;
	}
	cast_ray(game, &ray);
	draw_column(game, &ray, WIN_W / 2);
	draw_fisheye_demo(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

int	render_loop(t_game *game)
{
	render_frame(game);
	return (0);
}
