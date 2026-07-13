#include "cub3d.h"

void parse_grid_line(char *line , t_game *game)
{

    char **grid;
    int i;
    grid = malloc((game->map.height + 2) * sizeof(char *));
    i=0;
    while(i<game->map.height)
    {
        grid[i] = game->map.grid[i];
        i++;
    }
    grid[i] = ft_strdup(line);
    grid[i+1] = NULL;
 
    game->map.grid = grid;

    game->map.height++;
} 
