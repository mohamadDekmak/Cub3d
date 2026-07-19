#include "cub3d.h"

void	handle_movement(t_game *game)
{
	if (game->keys[KEY_W])
		move_player(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	if (game->keys[KEY_S])
		move_player(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	if (game->keys[KEY_D])
		move_player(game, game->player.plane_x * MOVE_SPEED,
			game->player.plane_y * MOVE_SPEED);
	if (game->keys[KEY_A])
		move_player(game, -game->player.plane_x * MOVE_SPEED,
			-game->player.plane_y * MOVE_SPEED);
	if (game->keys[KEY_RIGHT])
		rotate_player(game, ROT_SPEED);
	if (game->keys[KEY_LEFT])
		rotate_player(game, -ROT_SPEED);
}
