#include "cub3d.h"

static int maps_valid_character(char c)
{
    if(c == '0' || c == '1' || c=='N' || c=='S' || c == 'E' || c == 'W' || c == ' ')
        return 1;
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
        while(game->map.grid[x][y])
        {
            while(!maps_valid_character(game->map.grid[y][x]))
                return 1;
            if(game->map.grid[x][y] == 'N' || game->map.grid[x][y] == 'S' ||  game->map.grid[x][y] == 'E' || game->map.grid[x][y] == 'W'  )
                player_count++;
            x++;
        }
        y++;
    }
    if(player_count != 1)
        return 1;
    return 0;
        
}