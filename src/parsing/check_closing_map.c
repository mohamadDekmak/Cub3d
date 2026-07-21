/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closing_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 00:00:00 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-21 00:00:00 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_outside(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (1);
	return (0);
}

int	flood_fill(t_game *game, char **map, int x, int y)
{
	if (is_outside(game, x, y))
		return (1);
	if (map[y][x] == '1')
		return (0);
	if (map[y][x] == 'X')
		return (0);
	map[y][x] = 'X';
	if (flood_fill(game, map, x + 1, y))
		return (1);
	if (flood_fill(game, map, x - 1, y))
		return (1);
	if (flood_fill(game, map, x, y + 1))
		return (1);
	if (flood_fill(game, map, x, y - 1))
		return (1);
	return (0);
}

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (game->map.height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		copy[i] = ft_strdup(game->map.grid[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_copy(char **copy)
{
	int	i;

	i = 0;
	if (!copy)
		return ;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

int	check_closed_map(t_game *game)
{
	char	**copy;
	int		result;

	copy = copy_map(game);
	if (!copy)
		return (1);
	result = flood_fill(game, copy, (int)game->player.x, (int)game->player.y);
	free_copy(copy);
	if (result)
		return (error_exit(game, "Map is not closed"));
	return (0);
}
