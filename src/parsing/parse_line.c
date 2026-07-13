#include "cub3d.h"


int is_map_line(char *line)
{
    while (*line == ' ')
        line++;
    return (*line == '1' || *line == '0');
}

void parse_line(char *line, t_game *game)
{
    (void)game;

    if(ft_strncmp(line , "NO " ,3) ==0)
       parse_texture(line,game);
    else if (ft_strncmp(line, "SO " ,3) == 0)
       parse_texture(line,game);
    else if(ft_strncmp(line , "WE " , 3) ==0)
       parse_texture(line,game);
    else if(ft_strncmp(line , "EA " ,3) ==0)
       parse_texture(line,game);
     else if(ft_strncmp(line , "F " ,2) ==0)
      parse_color(line,game);
    else if(ft_strncmp(line , "C " ,2) ==0)
        parse_color(line,game);
    else if(is_map_line(line))
    {
        game->map.map_started = 1;
        parse_grid_line(line,game);
    }
  
}