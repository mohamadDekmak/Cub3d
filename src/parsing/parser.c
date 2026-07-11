#include "cub3d.h"

int parse_cub(char *filename, t_game *game)
{
    int fd;

    (void)game;
    fd = open(filename,O_RDONLY);
    if(check_extention(filename))
        return(error_exit(game,"invalid file text"));
    if(fd<1)
        return(error_exit(game,"cannot open file"));
    close(fd);
    printf("File open succesfully");
    return 0;
}