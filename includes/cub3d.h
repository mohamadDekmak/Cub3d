/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdekmak <mdekmak@student.42beirut.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-07-05 13:46:14 by mdekmak           #+#    #+#             */
/*   Updated: 2026-07-05 13:46:14 by mdekmak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
#include "../gnl/get_next_line.h"
/* -------------------------------------------------------------------------- */
/*  Config                                                                    */
/* -------------------------------------------------------------------------- */

# define WIN_W 1280
# define WIN_H 720
# define WIN_TITLE "cub3D"

/* Texture indices (used for tex_path[] and tex[]) */
# define NO 0
# define SO 1
# define WE 2
# define EA 3

/* Linux X11 keycodes */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* X11 events */
# define EVENT_KEYPRESS 2
# define EVENT_DESTROY 17

/* -------------------------------------------------------------------------- */
/*  Data structures                                                           */
/* -------------------------------------------------------------------------- */

/* One MiniLibX image buffer. We draw into .addr then push it to the window.  */
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Everything the parser produces from the .cub file.                         */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		fl_color;
	int		ce_color;
	char	*tex_path[4];
}	t_map;

/* The player: position + direction vector + camera plane.                    */
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* The single game context passed everywhere. No globals.                     */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		tex[4];
	t_map		map;
	t_player	player;
}	t_game;

/* -------------------------------------------------------------------------- */
/*  Prototypes                                                                */
/* -------------------------------------------------------------------------- */

/* events/ */
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);

/* utils/ */
int		error_exit(t_game *game, char *msg);
void	free_game(t_game *game);



//Parsing

int parse_cub(char *filename, t_game *game);
int check_extention(char *filename);
void parse_line(char *line, t_game *game);
#endif
