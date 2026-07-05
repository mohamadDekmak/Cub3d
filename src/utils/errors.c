/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-05 13:47:04 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-05 13:47:04 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	msglen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].ptr)
			mlx_destroy_image(game->mlx, game->tex[i].ptr);
		if (game->map.tex_path[i])
			free(game->map.tex_path[i]);
		i++;
	}
	if (game->frame.ptr)
		mlx_destroy_image(game->mlx, game->frame.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	error_exit(t_game *game, char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, msglen(msg));
		write(2, "\n", 1);
	}
	free_game(game);
	return (1);
}
