#include "cub3d.h"

static int maps_valid_character(char c)
{
    if(c == '0' || c == '1' || c=='N' || c=='S' || c == 'E' || c == 'W' || c == ' ')
        return (1);
    return 0;
}

int validate_map(t_game *game)
{
    int y;
    int x;
    int player_count;

    y=0;
    player_count =0;
    while (game->map.grid[y])
    {
        x=0;
        while(game->map.grid[y][x])
        {
        if (!maps_valid_character(game->map.grid[y][x]))
        {
            printf("Invalid character '%c' (ASCII %d) at [%d][%d]\n",
                game->map.grid[y][x],
                game->map.grid[y][x],
                y,
                x);
            return (error_exit(game, "Invalid map character"));
        }
            if (game->map.grid[y][x] == 'N' ||
                game->map.grid[y][x] == 'S' ||
                game->map.grid[y][x] == 'E' ||
                game->map.grid[y][x] == 'W')
                player_count++;
            x++;
        }
        y++;
    }
    if(player_count != 1)
        return 1;
    return 0;
        
}