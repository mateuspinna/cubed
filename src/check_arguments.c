/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:40:30 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/19 12:10:17 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_argc(int argc)
{
	if (argc != 2)
		return (1);
	return (0);
}

int	check_map(char *filename, char *ext, t_map_info *map)
{
	ft_memset(map, 0, sizeof(t_map_info));
	if (!filename || !ext || !ft_strrchr(filename, '.'))
		return (1);
	if (ft_strncmp(ft_strrchr(filename, '.'), ext, ft_strlen(ext) + 1))
		return (1);
	if (!read_map(map, filename))
	{
		clean_map(map);
		return (1);
	}
	map->row_nbr = array_size(map->map);
	map->col_nbr = ft_strlen(map->map[0]);
	return (0);
}
