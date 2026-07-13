#include "cub3d.h"

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
    else 
       parse_texture(line,game);
}