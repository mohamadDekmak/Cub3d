#include "cub3d.h"

static void strip_cr(char *line)
{
	int r;
	int w;

	r = 0;
	w = 0;
	while (line[r])
	{
		if (line[r] != '\r')
			line[w++] = line[r];
		r++;
	}
	line[w] = '\0';
}

int parse_cub(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	(void)	game;

	fd = open(filename, O_RDONLY);
	if (check_extention(filename))
		return(error_exit(game, "invalid file text"));
	if (fd < 1)
		return(error_exit(game, "cannot open file"));
	line = get_next_line(fd);
	while (line)
	{
		strip_cr(line);
		parse_line(line, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (validate_data(game))
		return (1);
	if (validate_map(game))
		return (1);
	printf("Parsing successful\n");
	return 0;
}