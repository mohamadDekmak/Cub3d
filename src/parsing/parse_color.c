#include "cub3d.h"

void parse_color(char *line , t_game *game)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line + 2, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	if(line[0] == 'F')
	{
		game->map.fl_color = get_rgb(r, g, b);
		game->map.floor_set = 1;
	}
	else
	{
		game->map.ce_color = get_rgb(r, g, b);
		game->map.ceiling_set = 1;
	}
}