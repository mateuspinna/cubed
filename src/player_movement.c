/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:17:20 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/07 16:17:22 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_sides(t_setup *set)
{
	float	side_x;
	float	side_y;

	side_x = set->player.dir_y * set->player.mov_speed;
	side_y = set->player.dir_x * set->player.mov_speed;
	if (set->states[4] && !set->states[5])
	{
		side_y *= -1;
		if (set->map_data.map[(int)(set->player.posy + side_y)]
			[(int)(set->player.posx + side_x)] != '1')
		{
			set->player.posx += side_x;
			set->player.posy += side_y;
		}
	}
	if (!set->states[4] && set->states[5])
	{
		side_x *= -1;
		if (set->map_data.map[(int)(set->player.posy + side_y)]
			[(int)(set->player.posx + side_x)] != '1')
		{
			set->player.posx += side_x;
			set->player.posy += side_y;
		}
	}
}

void	move_validation(t_setup *set)
{
	int		x;
	int		y;
	int		newx;
	int		newy;
	float	move_rate;

	x = (int)set->player.posx;
	y = (int)set->player.posy;
	move_rate = set->player.mov_speed * set->player.walk_direction;
	newx = (int)(set->player.posx + set->player.dir_x * move_rate);
	newy = (int)(set->player.posy + set->player.dir_y * move_rate);
	if (set->map_data.map[y][newx] != '1')
		set->player.posx += set->player.dir_x * move_rate;
	if (set->map_data.map[newy][x] != '1')
		set->player.posy += set->player.dir_y * move_rate;
	move_sides(set);
}

void	turn_player(t_setup *set)
{
	float	old_dir_x;
	float	old_plane_x;
	float	turn_rate;

	old_dir_x = set->player.dir_x;
	old_plane_x = set->player.plane_x;
	turn_rate = set->player.rot_speed * set->player.turn_direction;
	set->player.dir_x = set->player.dir_x * cos(turn_rate)
		- set->player.dir_y * sin(turn_rate);
	set->player.dir_y = old_dir_x * sin(turn_rate)
		+ set->player.dir_y * cos(turn_rate);
	set->player.plane_x = set->player.plane_x * cos(turn_rate)
		- set->player.plane_y * sin(turn_rate);
	set->player.plane_y = old_plane_x * sin(turn_rate)
		+ set->player.plane_y * cos(turn_rate);
}

void	check_states(t_setup *set)
{
	set->player.turn_direction = 0;
	if (set->states[0] || set->states[1])
	{
		if (set->states[0] && !set->states[1])
			set->player.turn_direction = 1;
		else if (!set->states[0] && set->states[1])
			set->player.turn_direction = -1;
	}
	set->player.walk_direction = 0;
	if (set->states[2] || set->states[3])
	{
		if (set->states[2] && !set->states[3])
			set->player.walk_direction = 1;
		else if (!set->states[2] && set->states[3])
			set->player.walk_direction = -1;
	}
}

void	move_player(t_setup *set)
{
	check_states(set);
	turn_player(set);
	move_validation(set);
}
