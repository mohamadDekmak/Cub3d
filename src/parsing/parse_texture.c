/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-21 00:00:00 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-21 00:00:00 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(char *line, t_game *game)
{
	char	*path;

	path = ft_strtrim(line + 2, " \n");
	if (ft_strncmp(line, "NO", 2) == 0)
		game->map.tex_path[NO] = path;
	else if (ft_strncmp(line, "SO", 2) == 0)
		game->map.tex_path[SO] = path;
	else if (ft_strncmp(line, "WE", 2) == 0)
		game->map.tex_path[WE] = path;
	else if (ft_strncmp(line, "EA", 2) == 0)
		game->map.tex_path[EA] = path;
}
