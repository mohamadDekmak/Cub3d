/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_maps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 00:00:00 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-21 00:00:00 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	maps_valid_character(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ')
		return (1);
	return (0);
}

static void	check_player_char(t_game *game, int x, int y, int *player_count)
{
	char	c;

	c = game->map.grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player_count)++;
		init_player(game, x, y, c);
	}
}

static int	validate_row(t_game *game, int y, int *player_count)
{
	int	x;

	x = 0;
	while (game->map.grid[y][x])
	{
		if (!maps_valid_character(game->map.grid[y][x]))
			return (error_exit(game, "Invalid map character"));
		check_player_char(game, x, y, player_count);
		x++;
	}
	return (0);
}

int	validate_map(t_game *game)
{
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (game->map.grid[y])
	{
		if (validate_row(game, y, &player_count))
			return (1);
		y++;
	}
	if (player_count != 1)
		return (error_exit(game, "Invalid player count"));
	if (check_closed_map(game))
		return (1);
	return (0);
}
