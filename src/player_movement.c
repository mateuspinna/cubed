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

int	is_wall(int x, int y, t_setup *set)
{
	int	pre_posy;

	pre_posy = floor(set->player.posy / TILE_SIZE);
	if (set->map_data.map[x][pre_posy] == '1'
			|| set->map_data.map[x][pre_posy] == ' ')
		return (1);
	if (set->map_data.map[x][y] == '1'
			|| set->map_data.map[x][y] == ' ')
		return (1);
	return (0);
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
	float	move_step;
	float	new_posx;
	float	new_posy;

	check_states(set);
	move_step = set->player.walk_direction * set->player.move_speed;
	set->player.rotation_angle += set->player.turn_direction
		* set->player.rotation_speed;
	new_posx = set->player.posx + (cos(set->player.rotation_angle) * move_step);
	new_posy = set->player.posy + (sin(set->player.rotation_angle) * move_step);
	if (!is_wall(floor(new_posx / TILE_SIZE), floor(new_posy / TILE_SIZE), set))
	{
		set->player.posx = new_posx;
		set->player.posy = new_posy;
	}
}
