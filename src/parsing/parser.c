#include "cub3d.h"

int parse_cub(char *filename, t_game *game)
{
    int fd;

    (void)game;
    fd = open(filename,O_RDONLY);
    if(check_extention(filename))
    if(fd<1)
    {
        printf("error cannot open .cub file:\n");
        return 1;
    }
    close(fd);
    printf("File open succesfully");
    return 0;
}