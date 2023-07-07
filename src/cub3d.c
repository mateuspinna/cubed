/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:44:43 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/06/29 16:22:40 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_next_frame(t_setup *set)
{
	if (set->has_changes)
	{
		move_player(set);
		render_floor_celling(set);
		render_minimap(set);
	}
	return (0);
}

void	start_game(t_setup *set)
{
	int	win_width;
	int	win_height;

	win_width = set->map_data.win_width;
	win_height = set->map_data.win_height;
	set->mlx = mlx_init();
	set->mlx_win = mlx_new_window(set->mlx, win_width, win_height, CUB);
	set->has_changes = 1;
	mlx_do_key_autorepeatoff(set->mlx);
	mlx_hook(set->mlx_win, 2, 1L << 0, key_event, set);
	mlx_hook(set->mlx_win, 3, 2L << 0, key_event_release, set);
	mlx_hook(set->mlx_win, 17, 0, close_win, set);
	mlx_loop_hook(set->mlx, render_next_frame, set);
	mlx_loop(set->mlx);
}

void	init_setup(t_setup *set)
{
	int	half_tile;

	half_tile = TILE_SIZE / 2;
	set->map_data.win_height = set->map_data.row_nbr * TILE_SIZE;
	set->map_data.win_width = set->map_data.col_nbr * TILE_SIZE;
	set->player.posx = (set->map_data.player_posx * TILE_SIZE) + half_tile;
	set->player.posy = (set->map_data.player_posy * TILE_SIZE) + half_tile;
	set->player.height = 8 * MINIMAP_SCALE;
	set->player.width = 8 * MINIMAP_SCALE;
	set->player.turn_direction = 0;
	set->player.walk_direction = 0;
	set->player.rotation_angle = PI / 2;
	set->player.move_speed = 0.2;
	set->player.rotation_speed = 0.4 * (PI / 180);
}

int	main(int argc, char **argv)
{
	t_setup	game_setup;

	if (check_argc(argc))
		return (print_error(ARG_ERROR, 1));
	if (check_map(argv[1], EXT, &game_setup.map_data))
		return (print_error(EXT_ERROR, 1));
	init_setup(&game_setup);
	start_game(&game_setup);
	clean_map(&game_setup.map_data);
	return (0);
}

// t_data	square_img(int width, int height, int color, void *mlx)
// {
// 	t_data	sqr;
// 	int		x;
// 	int		y;

// 	x = -1;
// 	sqr.img = mlx_new_image(mlx, width, height);
// 	sqr.addr = mlx_get_data_addr(sqr.img, &sqr.bpp, &sqr.line_len, &sqr.endian);
// 	while (++x < width)
// 	{
// 		y = -1;
// 		while (++y < height)
// 			my_mlx_pixel_put(&sqr, x, y, color);
// 	}	
// 	return (sqr);
// }
