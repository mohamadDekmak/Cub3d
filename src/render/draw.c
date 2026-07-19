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

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	t_img	*tex;
	double	step;
	double	tex_pos;

	tex = &game->tex[pick_tex_index(ray)];
	tex_x = compute_tex_x(ray, tex);
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * step;
	y = 0;
	while (y < WIN_H)
	{
		if (y < ray->draw_start)
			my_pixel_put(&game->frame, x, y, game->map.ce_color);
		else if (y > ray->draw_end)
			my_pixel_put(&game->frame, x, y, game->map.fl_color);
		else
		{
			tex_y = (int)tex_pos;
			if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			my_pixel_put(&game->frame, x, y, get_tex_pixel(tex, tex_x, tex_y));
			tex_pos += step;
		}
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
