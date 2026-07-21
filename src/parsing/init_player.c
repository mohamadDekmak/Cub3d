/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 00:00:00 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-21 00:00:00 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir_ns(t_player *player, char dir)
{
	player->dir_x = 0;
	player->plane_y = 0;
	if (dir == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
}

static void	set_dir_ew(t_player *player, char dir)
{
	player->dir_y = 0;
	player->plane_x = 0;
	if (dir == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
}

static void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_dir_ns(player, dir);
	else if (dir == 'E' || dir == 'W')
		set_dir_ew(player, dir);
}

void	init_player(t_game *game, int x, int y, char direction)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	set_player_direction(&game->player, direction);
}
