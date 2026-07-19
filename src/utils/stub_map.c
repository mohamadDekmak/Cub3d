#include "cub3d.h"

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
	game->map.fl_color = (46 << 16) | (49 << 8) | 54;
	game->map.ce_color = (5 << 16) | (7 << 8) | 15;
	game->map.tex_path[NO] = ft_strdup("./textures/north.xpm");
	game->map.tex_path[SO] = ft_strdup("./textures/south.xpm");
	game->map.tex_path[WE] = ft_strdup("./textures/west.xpm");
	game->map.tex_path[EA] = ft_strdup("./textures/east.xpm");
	game->player.x = 4.5;
	game->player.y = 3.5;
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
}
