#include "cub3d.h"

void parse_line(char *line, t_game *game)
{
    (void)game;

    if(ft_strncmp(line , "NO " ,3) ==0)
    {
        printf("North TEXTURE\n");
    }
    else if (ft_strncmp(line, "SO " ,3) == 0)
    {
        printf("South TEXTURE\n");
    }
    else if(ft_strncmp(line , "WE " , 3) ==0)
    {
        printf("WEST TEXTURE\n");
    }
    else if(ft_strncmp(line , "EA " ,3) ==0)
    {
        printf("EAST TEXTURE\n");
    }
     else if(ft_strncmp(line , "F " ,2) ==0)
    {
        printf("Floor COLOR\n");
    }
    else if(ft_strncmp(line , "C " ,2) ==0)
    {
        printf("CEILING COLOR\n");
    }
    else 
    {
        printf("MAP LINE : %s" , line);
    }
}