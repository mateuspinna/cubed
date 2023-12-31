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
		close_win(set);
	if (keycode == R_KEY)
		set->states[0] = 1;
	if (keycode == L_KEY)
		set->states[1] = 1;
	if (keycode == W)
		set->states[2] = 1;
	if (keycode == S)
		set->states[3] = 1;
	if (keycode == A)
		set->states[4] = 1;
	if (keycode == D)
		set->states[5] = 1;
	return (0);
}

int	key_event_release(int keycode, t_setup *set)
{
	if (keycode == R_KEY)
		set->states[0] = 0;
	if (keycode == L_KEY)
		set->states[1] = 0;
	if (keycode == W)
		set->states[2] = 0;
	if (keycode == S)
		set->states[3] = 0;
	if (keycode == A)
		set->states[4] = 0;
	if (keycode == D)
		set->states[5] = 0;
	return (0);
}

int	close_win(t_setup *set)
{
	mlx_destroy_window(set->mlx, set->mlx_win);
	clean_textures(set);
	clean_map(&set->map_data);
	exit(EXIT_FAILURE);
}
