/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:24:33 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/12 17:31:56 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(t_map_info *data, int i, int j, int *flag)
{
	if (data->map[i][j] == ' ')
	{
		*flag += 1;
		return ;
	}
	if (data->map[i][j] == '1')
		return ;
	data->map[i][j] = '1';
	flood_fill(data, i + 1, j, flag);
	flood_fill(data, i - 1, j, flag);
	flood_fill(data, i, j + 1, flag);
	flood_fill(data, i, j - 1, flag);
	return ;
}
