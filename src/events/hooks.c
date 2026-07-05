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

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_close(game);
	return (0);
}

int	handle_close(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
