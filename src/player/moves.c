#include "cub3d.h"

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (!is_wall(game, (int)new_x, (int)game->player.y))
		game->player.x = new_x;
	if (!is_wall(game, (int)game->player.x, (int)new_y))
		game->player.y = new_y;
}
