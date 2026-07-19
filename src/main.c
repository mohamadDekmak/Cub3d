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
	ft_bzero(game, sizeof(t_game));
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
	game->frame.width = WIN_W;
	game->frame.height = WIN_H;
	mlx_hook(game->win, EVENT_KEYPRESS, 1L << 0,
		(int (*)(void))(void *)handle_keydown, game);
	mlx_hook(game->win, EVENT_KEYRELEASE, 1L << 1,
		(int (*)(void))(void *)handle_keyup, game);
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
	/*
	if(parse_cub(argv[1], &game))
		return 1;
	if (validate_map(&game))
		return (error_exit(&game, "Invalid map"));
	*/
	load_stub(&game);
	printf("[stub] map %dx%d, player at (%.2f, %.2f)\n",
		game.map.width, game.map.height, game.player.x, game.player.y);

	if (setup_window(&game) != 0)
		return (1);
	mlx_loop_hook(game.mlx, (int (*)(void))(void *)render_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
