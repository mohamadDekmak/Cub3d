#include "cub3d.h"

void parse_grid_line(char *line , t_game *game)
{

    char **grid;
    char *tmp;
    int i;
    grid = malloc((game->map.height + 2) * sizeof(char *));
    if(!grid)
        return;
    i=0;
    while(i<game->map.height)
    {
        grid[i] = game->map.grid[i];
        i++;
    }
    tmp = ft_strtrim(line, "\n");
    grid[i] = tmp;
    grid[i+1] = NULL;
    free(game->map.grid);
    game->map.grid = grid;
    game->map.height++;
} 
