#include "cub3d.h"

void	render_frame(t_game *game)
{
	int	x;
	int	y;

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
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

int	render_loop(t_game *game)
{
	render_frame(game);
	return (0);
}
