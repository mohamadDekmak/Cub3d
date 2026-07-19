#include "cub3d.h"

int	load_textures(t_game *game)
{
	int	i;
	int	w;
	int	h;

	i = 0;
	while (i < 4)
	{
		game->tex[i].ptr = mlx_xpm_file_to_image(game->mlx,
				game->map.tex_path[i], &w, &h);
		if (!game->tex[i].ptr)
			return (error_exit(game, "failed to load texture"));
		game->tex[i].width = w;
		game->tex[i].height = h;
		game->tex[i].addr = mlx_get_data_addr(game->tex[i].ptr,
				&game->tex[i].bpp, &game->tex[i].line_len,
				&game->tex[i].endian);
		i++;
	}
	return (0);
}
