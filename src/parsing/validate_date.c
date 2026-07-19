#include "cub3d.h"

int validate_textures(t_game *game)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (!game->map.tex_path[i])
            return (error_exit(game, "Missing texture"));

        i++;
    }
    return (0);
}
static int check_texture_files(t_game *game)
{
    int i;
    int fd;

    i = 0;
    while (i < 4)
    {
        fd = open(game->map.tex_path[i], O_RDONLY);
        if (fd < 0)
            return (error_exit(game, "Cannot open texture"));

        close(fd);
        i++;
    }
    return (0);
}

static int check_colors(t_game *game)
{
    if (!game->map.floor_set)
        return (error_exit(game, "Missing floor color"));

    if (!game->map.ceiling_set)
        return (error_exit(game, "Missing ceiling color"));

    return (0);
}

int validate_data(t_game *game)
{
    if (validate_textures(game))
        return (1);

    if (check_texture_files(game))
        return (1);

    if (check_colors(game))
        return (1);

    return (0);
}