/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:44:43 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/08/14 18:01:07 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_next_frame(t_setup *set)
{
	move_player(set);
	render_floor_celling(set);
	cast_all_rays(set);
	usleep(100);
	mlx_put_image_to_window(set->mlx, set->mlx_win, set->frame.img, 0, 0);
	mlx_destroy_image(set->mlx, set->frame.img);
	return (0);
}

void	start_game(t_setup *set)
{
	set->mlx = mlx_init();
	set->mlx_win = mlx_new_window(set->mlx, WIDTH, HEIGHT, CUB);
	init_texture(set);
	mlx_do_key_autorepeatoff(set->mlx);
	mlx_hook(set->mlx_win, 2, 1L << 0, key_event, set);
	mlx_hook(set->mlx_win, 3, 2L << 0, key_event_release, set);
	mlx_hook(set->mlx_win, 17, 0, close_win, set);
	mlx_loop_hook(set->mlx, render_next_frame, set);
	mlx_loop(set->mlx);
}

void	set_player_direction(t_setup *set)
{
	if (set->map_data.orientation == 'S')
	{
		set->player.dir_y = 1;
		set->player.plane_x = -0.66;
	}
	if (set->map_data.orientation == 'N')
	{
		set->player.dir_y = -1;
		set->player.plane_x = 0.66;
	}
	if (set->map_data.orientation == 'W')
	{
		set->player.dir_x = -1;
		set->player.plane_y = -0.66;
	}
	if (set->map_data.orientation == 'E')
	{
		set->player.dir_x = 1;
		set->player.plane_y = 0.66;
	}
}

void	init_setup(t_setup *set)
{
	set->states[0] = 0;
	set->states[1] = 0;
	set->states[2] = 0;
	set->states[3] = 0;
	set->states[4] = 0;
	set->states[5] = 0;
	set->map_data.win_height = HEIGHT;
	set->map_data.win_width = WIDTH;
	set->player.posx = set->map_data.player_posx + 0.5;
	set->player.posy = set->map_data.player_posy + 0.5;
	set->player.height = 8 * MINIMAP_SCALE;
	set->player.width = 8 * MINIMAP_SCALE;
	set->player.turn_direction = 0;
	set->player.walk_direction = 0;
	set->player.dir_x = 0;
	set->player.dir_y = 0;
	set->player.plane_x = 0;
	set->player.plane_y = 0;
	set_player_direction(set);
	set->player.mov_speed = 0.02;
	set->player.rot_speed = 0.01;
}

int	main(int argc, char **argv)
{
	t_setup	set;

	if (check_argc(argc))
		return (print_error(ARG_ERROR, 1));
	if (check_map(argv[1], EXT, &set.map_data))
		return (print_error(EXT_ERROR, 1));
	init_setup(&set);
	start_game(&set);
	clean_textures(&set);
	clean_map(&set.map_data);
	return (0);
}
