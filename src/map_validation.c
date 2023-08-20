/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:40:40 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/05/20 17:20:23 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_open(char **map);

int	check_map_content(char **map, t_map_info *info)
{
	int	i;
	int	j;
	int	flags[2];

	ft_memset(flags, 0, sizeof(int) * 2);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(MAP_CHARS, map[i][j]))
				flags[0] = 1;
			if (ft_strchr(DIR_CHARS, map[i][j]))
			{
				info->orientation = map[i][j];
				info->player_posx = j - 1;
				info->player_posy = i - 1;
				flags[1]++;
			}
		}
	}	
	if (flags[0] || flags[1] != 1)
		return (1);
	return (0);
}

void	format_map(t_map_info *map_data)
{
	int		max_length;
	int		i;
	char	**new_array;
	int		size;
	int		spaces_needed;

	size = array_size(map_data->map);
	max_length = max_line_length(map_data->map);
	i = -1;
	new_array = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
	{
		spaces_needed = max_length - ft_strlen(map_data->map[i]);
		new_array[i] = add_n_char(map_data->map[i], ' ', spaces_needed);
	}
	new_array[i] = NULL;
	free_array(map_data->map);
	map_data->map = new_array;
}

int	validate_map(char **map, int size, int i, t_map_info *info)
{
	char	**space_box;
	char	*temp;
	int		max_len;

	max_len = max_line_length(map) + 2;
	space_box = malloc(sizeof(char *) * (size + 3));
	space_box[i] = add_n_char("", ' ', max_len);
	while (*map)
	{
		temp = ft_strjoin(" ", *map++);
		space_box[++i] = add_n_char(temp, ' ', 1);
		free(temp);
	}
	space_box[++i] = add_n_char("", ' ', max_len);
	space_box[++i] = NULL;
	if (check_map_content(space_box, info) || is_map_open(space_box))
	{
		free_array(space_box);
		return (1);
	}
	free_array(space_box);
	return (0);
}

int	is_map_open(char **my_map)
{
	t_map_info	data;
	int			rows_coll[2];
	int			i;
	int			j;
	int			flag;

	rows_coll[0] = array_size(my_map);
	rows_coll[1] = ft_strlen(my_map[0]);
	i = -1;
	flag = 0;
	data.map = my_map;
	while (++i < rows_coll[0])
	{
		j = -1;
		while (++j < rows_coll[1])
		{
			if (data.map[i][j] != ' ' && data.map[i][j] != '1')
				flood_fill(&data, i, j, &flag);
			if (flag)
				return (1);
		}
	}	
	return (0);
}

int	is_map_valid(t_map_info *map_data)
{
	int	size;

	size = array_size(map_data->map);
	format_map(map_data);
	return (validate_map(map_data->map, size, 0, map_data));
}
