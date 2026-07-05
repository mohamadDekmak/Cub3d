/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-05 13:47:08 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-05 13:47:08 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->frame.ptr = NULL;
}

static int	setup_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_exit(game, "mlx_init failed"));
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN_TITLE);
	if (!game->win)
		return (error_exit(game, "mlx_new_window failed"));
	game->frame.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->frame.ptr)
		return (error_exit(game, "mlx_new_image failed"));
	game->frame.addr = mlx_get_data_addr(game->frame.ptr,
			&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	mlx_hook(game->win, EVENT_KEYPRESS, 1L << 0,
		(int (*)(void))(void *)handle_keypress, game);
	mlx_hook(game->win, EVENT_DESTROY, 0,
		(int (*)(void))(void *)handle_close, game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	init_game(&game);
	if (setup_window(&game) != 0)
		return (1);
	mlx_loop(game.mlx);
	return (0);
}
