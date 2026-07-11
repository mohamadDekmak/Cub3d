#include "cub3d.h"

int check_extention(char *filename)
{
    int len;
    len = ft_strlen(filename);

    if(len<5)
        return 1;
    if(filename[len - 4] != '.' || filename[len - 3] != 'c' || filename[len - 2] != 'u' ||filename[len - 1] != 'b')
        return 1;
    return 0;
}