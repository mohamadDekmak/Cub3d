/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 00:00:00 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-21 00:00:00 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
