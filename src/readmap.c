/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:52:10 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/13 19:09:19 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	save_path(t_map_info *map_data, char *line);
int	save_color(t_map_info *map_data, char *line);
int	save_map(t_map_info *map_data, char *line, int fd);

int	read_map(t_map_info *map_data, char *filename)
{
	char	*line;
	int		fd;
	int		is_valid;

	is_valid = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (*line == 'S' || *line == 'N' || *line == 'E' || *line == 'W')
			is_valid = save_path(map_data, line);
		else if ((*line == 'F' || *line == 'C') && !is_valid)
			is_valid = save_color(map_data, line);
		else if (*line != '\n' && !is_valid)
			is_valid = save_map(map_data, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map_data->fields_filled != 4 || is_valid)
		return (0);
	return (1);
}

int	save_path(t_map_info *map_data, char *line)
{
	char	*path_add;
	int		len;
	int		fd;

	len = ft_strlen(ft_strrchr(line, ' ') + 1);
	path_add = ft_substr(ft_strrchr(line, ' ') + 1, 0, len - 1);
	fd = open(path_add, O_RDONLY);
	if (!ft_strncmp(line, "NO", 2) && line[2] == ' ' && !map_data->n_path)
		map_data->n_path = ft_substr(path_add, 0, ft_strlen(path_add));
	else if (!ft_strncmp(line, "SO", 2) && line[2] == ' ' && !map_data->s_path)
		map_data->s_path = ft_substr(path_add, 0, ft_strlen(path_add));
	else if (!ft_strncmp(line, "WE", 2) && line[2] == ' ' && !map_data->w_path)
		map_data->w_path = ft_substr(path_add, 0, ft_strlen(path_add));
	else if (!map_data->e_path && line[2] == ' ')
		map_data->e_path = ft_substr(path_add, 0, ft_strlen(path_add));
	else
	{
		free(path_add);
		return (1);
	}
	free(path_add);
	if (fd == -1)
		return (1);
	map_data->fields_filled++;
	return (0);
}

int	ft_strrgb(char *color_code)
{
	char	**rgb_array;
	int		i;
	int		j;
	int		rgb_value[4];

	i = -1;
	rgb_array = ft_split(color_code, ',');
	rgb_value[3] = 0;
	while (rgb_array[++i] && rgb_value[3] != -1)
	{	
		j = 0;
		while (rgb_array[i][j] && rgb_array[i][j] != '\n')
		{
			if (rgb_array[i][j] < '0' || rgb_array[i][j] > '9' || j > 2)
				rgb_value[3] = -1;
			j++;
		}
		rgb_value[i] = ft_atoi(rgb_array[i]);
		if (rgb_value[i] > 255)
			rgb_value[3] = -1;
	}
	free_array(rgb_array);
	if (rgb_value[3] == -1 || i != 3)
		return (-1);
	return (rgb_value[0] << 16 | rgb_value[1] << 8 | rgb_value[2]);
}

int	save_color(t_map_info *map_data, char *line)
{
	static int	check_rep[2];
	char		*color_code;
	int			rgb_color;

	color_code = ft_strdup(ft_strrchr(line, ' ') + 1);
	rgb_color = ft_strrgb(color_code);
	free(color_code);
	if (rgb_color == -1)
		return (1);
	else if (!ft_strncmp(line, "F", 1) && line[1] == ' ' && !check_rep[0])
	{
		check_rep[0] = 1;
		map_data->f_color = rgb_color;
	}
	else if (!ft_strncmp(line, "C", 1) && line[1] == ' ' && !check_rep[1])
	{
		check_rep[1] = 1;
		map_data->c_color = rgb_color;
	}
	else
		return (1);
	return (0);
}

int	save_map(t_map_info *map_data, char *line, int fd)
{
	char	*curr_line;
	int		size;

	size = array_size(map_data->map);
	map_data->map = add_string(NULL, line, size);
	curr_line = get_next_line(fd);
	while (curr_line)
	{
		if (*curr_line == '\n')
			return (1);
		size = array_size(map_data->map);
		map_data->map = add_string(map_data->map, curr_line, size);
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	free(curr_line);
	if (is_map_valid(map_data))
		return (1);
	return (0);
}
