/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:23:02 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/19 17:10:17 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	array_size(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	**add_string(char **array, char *str, int size)
{
	int		i;
	char	**new_array;

	i = -1;
	new_array = malloc(sizeof(char *) * (size + 2));
	while (++i < size)
		new_array[i] = ft_strdup(array[i]);
	if (ft_strrchr(str, '\n'))
		new_array[i] = ft_substr(str, 0, ft_strlen(str) - 1);
	else
		new_array[i] = ft_strdup(str);
	new_array[++i] = NULL;
	free_array(array);
	return (new_array);
}

void	print_str_array(char **array)
{
	if (!array)
		return ;
	while (*array)
		printf("%s\n", *array++);
}

char	*add_n_char(char *str, char c, int n)
{
	int		size;
	char	*added;
	int		added_size;
	int		i;

	i = 0;
	size = ft_strlen(str);
	added_size = size + n;
	added = malloc(sizeof(char) * (added_size + 1));
	while (*str)
		added[i++] = *str++;
	while (n-- > 0)
		added[i++] = c;
	added[i] = 0;
	return (added);
}

int	max_line_length(char **array)
{
	int	i;
	int	j;
	int	length;

	length = 0;
	i = -1;
	if (array)
	{
		while (array[++i])
		{
			j = 0;
			while (array[i][j])
				j++;
			if (j > length)
				length = j;
		}
	}
	return (length);
}
