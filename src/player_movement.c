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

int	is_wall(int x, int y, char **map, float posy)
{
	int	coordinate_y;

	coordinate_y = floor(posy / TILE_SIZE);
	if (map[x][coordinate_y] == '1' || map[x][coordinate_y] == ' ')
		return (1);
	if (map[x][y] == '1' || map[x][y] == ' ')
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
	int		posx_on_map;
	int		posy_on_map;

	check_states(set);
	move_step = set->player.walk_direction * set->player.move_speed;
	set->player.rotation_angle += set->player.turn_direction
		* set->player.rotation_speed;
	new_posx = set->player.posx + (cos(set->player.rotation_angle) * move_step);
	new_posy = set->player.posy + (sin(set->player.rotation_angle) * move_step);
	posx_on_map = floor(new_posx / TILE_SIZE);
	posy_on_map = floor(new_posy / TILE_SIZE);
	if (!is_wall(posx_on_map, posy_on_map, set->map_data.map, set->player.posy))
	{
		set->player.posx = new_posx;
		set->player.posy = new_posy;
	}
}
