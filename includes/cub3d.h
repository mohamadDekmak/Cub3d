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
# define EVENT_KEYRELEASE 3
# define EVENT_DESTROY 17

/* Movement/rotation step sizes — per-frame now (Stage 9), not per-keypress */
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

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
	int 	floor_set;
    int 	ceiling_set;
	char	*tex_path[4];
	int		map_started;
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
	int			keys[65536];
}	t_game;

/* One ray's working state during a DDA cast. Filled in and read back by      */
/* the raycasting functions in src/render/ — not touched by the parser.      */
/* Grows stage by stage: camera_x arrives in Stage 6 (FOV sweep).             */
typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	distance_to_next_vertical_line;
	double	distance_to_next_horizontal_line;
	double	distance_between_vertical_lines;
	double	distance_between_horizontal_lines;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* -------------------------------------------------------------------------- */
/*  Prototypes                                                                */
/* -------------------------------------------------------------------------- */

/* events/ */
int		handle_keydown(int keycode, t_game *game);
int		handle_keyup(int keycode, t_game *game);
int		handle_close(t_game *game);

/* render/ */
int		get_rgb(int r, int g, int b);
void	my_pixel_put(t_img *img, int x, int y, int color);
int		get_tex_pixel(t_img *tex, int x, int y);
void	render_frame(t_game *game);
int		render_loop(t_game *game);
int		is_wall(t_game *game, int map_x, int map_y);
void	cast_ray(t_game *game, t_ray *ray, int x);
void	draw_column(t_game *game, t_ray *ray, int x);
int		load_textures(t_game *game);

/* player/ */
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double angle);
void	handle_movement(t_game *game);

/* utils/ */
int		error_exit(t_game *game, char *msg);
void	free_game(t_game *game);



//Parsing

int parse_cub(char *filename, t_game *game);
int check_extention(char *filename);
void parse_line(char *line, t_game *game);
void parse_texture(char *line , t_game *game);
void parse_color(char *line , t_game *game);
void parse_grid_line(char *line , t_game *game);
int validate_map(t_game *game);
void init_player(t_game *game, int x, int y, char direction);
int check_closed_map(t_game *game);
int validate_data(t_game *game);
#endif
