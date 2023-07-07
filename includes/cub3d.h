/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:48:11 by vsergio           #+#    #+#             */
/*   Updated: 2023/05/21 15:52:13 by mpinna-l         ###   ########.fr       */
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

# else
#  include "../mlx/mlx.h"
#  define ESC 53
#  define R_KEY 124
#  define L_KEY 123
#  define U_KEY 126
#  define D_KEY 125

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
# define EXT_ERROR "Error\nInvalid Map! Check if it exists, it's extention or\
if the data inside it is correct!\n"
# define MAP_CHARS "01 NSEW"
# define DIR_CHARS "NSEW"
/* _______________________CONSTANTS___________________________ */

# define MINIMAP_SCALE 0.2
# define TILE_SIZE 32
# define PI 3.14159265
# define TWO_PI 6.28318530
/* # define FOV_ANGLE (60 * (PI / 180)) */

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
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;	
}	t_player;

typedef struct s_setup
{
	void		*mlx;
	void		*mlx_win;
	t_data		frame;
	t_map_info	map_data;
	t_player	player;
	int			has_changes;
}	t_setup;	

/* _______________________Functions_________________________ */

// error handling
int			print_error(char *error_str, int return_value);

// argument checking
int			check_argc(int argc);
int			check_map(char *filename, char *ext, t_map_info *map_data);

// reading map
int			read_map(t_map_info *map_data, char *filename);

// map validation
int			is_map_valid(t_map_info *map_data);
void		format_map(t_map_info *map_data);
void		flood_fill(t_map_info *data, int i, int j, int *flag);
int			rgb_color(int red, int green, int blue);

// render functions
void		set_color(int *color, int i, int j, t_setup *set);
void		render_minimap(t_setup *set);
void		render_player(t_setup *set);
void		render_floor_celling(t_setup *set);

// player moviment
void		move_player(t_setup *set);
int			is_wall(int x, int y, t_setup *set);

// array utils
int			array_size(char **array);
char		**add_string(char **array, char *str, int size);
void		print_str_array(char **array);
int			max_line_length(char **array);
char		*add_n_char(char *str, char c, int n);

// utils
void		free_array(char **str_array);
void		clean_map(t_map_info *map_data);
void		init_data(t_data *info);
t_data		square_img(int width, int height, int color, void *mlx);

// hooks
int			key_event(int keycode, t_setup *info);
int			key_event_release(int keycode, t_setup *info);
int			close_win(t_setup *info);

void		my_mlx_pixel_put(t_data *info, int x, int y, int color);
void		render_background(t_data *info);

#endif
