/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:48:11 by mpinna-l           #+#    #+#            */
/*   Updated: 2023/07/15 10:11:07 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# if defined(__linux__)
#  include "../mlx_linux/mlx.h"
#  define ESC 65307
#  define R_KEY 65363
#  define L_KEY 65361
#  define U_KEY 65362
#  define D_KEY 65364
#  define W 119
#  define S 115
#  define A 97
#  define D 100

# else
#  include "../mlx/mlx.h"
#  define ESC 53
#  define R_KEY 124
#  define L_KEY 123
#  define U_KEY 126
#  define D_KEY 125
#  define W 13
#  define S 1
#  define A 0
#  define D 2

# endif
// Minilib X funtions

# include "libft/libft.h"
// Set of utility

# include <stdlib.h>
// exit, malloc, free

# include <stdio.h>
// printf

# include <unistd.h>
// write, read, close

# include <fcntl.h>
// open

# include <errno.h>
// strerror, perror

# include <math.h>
// all functions from this lib

/* _______________________Color Section___________________ */

# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define FUCHSIA 0xFF00FF
# define CYAN 0x00FFFF
# define WHITE 0xFFFFFF

/* ___________________String Defines_______________________ */

# define CUB "cub3d"
# define ARG_ERROR "Error\nWrong number of arguments!\nUsage: ./cub3d <map.cub>\n"
# define EXT ".cub"
# define EXT_ERROR "Error\nInvalid Map! Check if map exists, it's extention and\
 if the map has the correct data set!\n"
# define MAP_CHARS "01 NSEW"
# define DIR_CHARS "NSEW"
/* _______________________CONSTANTS___________________________ */

# define MINIMAP_SCALE 0.2
# define TILE_SIZE 32
# define PI 3.14159265
# define TWO_PI 6.28318530
# define HEIGHT 600
# define WIDTH 800
# define T_HEIGHT 64
# define T_WIDTH 64
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
/* ________________________Structs_________________________ */

typedef struct s_map_info
{
	char	*s_path;
	char	*n_path;
	char	*e_path;
	char	*w_path;
	int		f_color;
	int		c_color;
	int		fields_filled;
	char	**map;
	int		row_nbr;
	int		col_nbr;
	char	orientation;
	int		player_posx;
	int		player_posy;
	int		win_width;
	int		win_height;
	int		color_picker;
}	t_map_info;

typedef struct s_data
{
	void	*img;
	void	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_player
{
	float	posx;
	float	posy;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	rot_speed;
	float	mov_speed;
}	t_player;

typedef struct s_rays
{
	float	camera_x;
	float	ray_dirx;
	float	ray_diry;
	int		map_x;
	int		map_y;
	float	side_distx;
	float	side_disty;
	float	delta_distx;
	float	delta_disty;
	float	distance;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	float	wall_hit_x;
	int		texture_index;
	int		tex_x;
}	t_rays;

typedef struct s_texture
{
	int		height;
	int		width;
	t_data	texture_img;
}	t_texture;

typedef struct s_setup
{
	void		*mlx;
	void		*mlx_win;
	int			states[6];
	t_data		frame;
	t_map_info	map_data;
	t_player	player;
	t_texture	texture[4];
}	t_setup;

/* _______________________Functions_________________________ */

// Error handling
int			print_error(char *error_str, int return_value);

// Argument checking
int			check_argc(int argc);
int			check_map(char *filename, char *ext, t_map_info *map_data);

// Reading map
int			read_map(t_map_info *map_data, char *filename);

// Map validation
int			is_map_valid(t_map_info *map_data);
void		format_map(t_map_info *map_data);
void		flood_fill(t_map_info *data, int i, int j, int *flag);
int			rgb_color(int red, int green, int blue);

// Render functions
void		render_floor_celling(t_setup *set);
void		render_strip(int x, t_rays *ray, t_setup *set, int *tex);

// Player moviment
void		move_player(t_setup *set);
void		move_validation(t_setup *set);

// Raycasting
void		cast_all_rays(t_setup *set);

// Texture
void		init_texture(t_setup *set);
void		set_texture_details(t_rays *ray);
void		clean_textures(t_setup *set);
int			get_pixel_color(t_texture texture, int x, int y);

// Array utils
int			array_size(char **array);
char		**add_string(char **array, char *str, int size);
void		print_str_array(char **array);
int			max_line_length(char **array);
char		*add_n_char(char *str, char c, int n);

// Utils
void		free_array(char **str_array);
void		clean_map(t_map_info *map_data);

// Hooks
int			key_event(int keycode, t_setup *info);
int			key_event_release(int keycode, t_setup *info);
int			close_win(t_setup *info);

void		my_mlx_pixel_put(t_data *info, int x, int y, int color);

#endif
