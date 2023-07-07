/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:51:07 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/06/29 16:21:24 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_event(int keycode, t_setup *set)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(set->mlx, set->mlx_win);
		exit(EXIT_FAILURE);
	}
	if (keycode == R_KEY)
		set->player.turn_direction = 1;
	else if (keycode == L_KEY)
		set->player.turn_direction = -1;
	else if (keycode == U_KEY)
		set->player.walk_direction = 1;
	else if (keycode == D_KEY)
		set->player.walk_direction = -1;
	else
		return (0);
	set->has_changes = 1;
	return (0);
}

int	key_event_release(int keycode, t_setup *set)
{
	if (keycode == R_KEY)
		set->player.turn_direction = 0;
	else if (keycode == L_KEY)
		set->player.turn_direction = 0;
	else if (keycode == U_KEY)
		set->player.walk_direction = 0;
	else if (keycode == D_KEY)
		set->player.walk_direction = 0;
	else
		return (0);
	set->has_changes = 0;
	return (0);
}

int	close_win(t_setup *set)
{
	mlx_destroy_window(set->mlx, set->mlx_win);
	exit(1);
}
