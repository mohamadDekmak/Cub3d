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

/* STAGE 9 — just record key state; the actual movement happens once per
 * frame in handle_movement(), so held keys move smoothly. */
int	handle_keydown(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	else if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 1;
	return (0);
}

int	handle_keyup(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

int	handle_close(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
