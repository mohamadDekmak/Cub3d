/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-05 13:46:51 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-05 13:46:51 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* STAGE 8 — v1: one step per keypress event, no held-key smoothness.
 * Replaced by a key-state array in Stage 9. */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	else if (keycode == KEY_W)
		move_player(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	else if (keycode == KEY_S)
		move_player(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	else if (keycode == KEY_D)
		move_player(game, game->player.plane_x * MOVE_SPEED,
			game->player.plane_y * MOVE_SPEED);
	else if (keycode == KEY_A)
		move_player(game, -game->player.plane_x * MOVE_SPEED,
			-game->player.plane_y * MOVE_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, ROT_SPEED);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
	return (0);
}

int	handle_close(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
