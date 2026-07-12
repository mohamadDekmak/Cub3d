#include "cub3d.h"

/* TEMPORARY — delete once parse_cub() populates game->map/player for real.
 * See Stage 13 of the raycasting plan. This hand-fills the exact same
 * fields the real parser will eventually produce (map grid, dimensions,
 * floor/ceiling color, player spawn), mirroring maps/valid/simple.cub,
 * so early rendering work has real data before parsing is finished. */

static char	*g_stub_rows[5] = {
	"111111",
	"100101",
	"101001",
	"1100N1",
	"111111"
};

void	load_stub(t_game *game)
{
	int	i;

	game->map.height = 5;
	game->map.width = 6;
	game->map.grid = malloc(sizeof(char *) * game->map.height);
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = ft_strdup(g_stub_rows[i]);
		i++;
	}
	game->map.fl_color = (220 << 16) | (100 << 8) | 0;
	game->map.ce_color = (225 << 16) | (30 << 8) | 0;
	game->player.x = 4.5;
	game->player.y = 3.5;
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
}
