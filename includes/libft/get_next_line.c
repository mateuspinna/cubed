/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 09:00:31 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/12 15:59:16 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_full_text(int fd, char *txt)
{
	int		chars_read;
	char	*buffer;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	chars_read = 1;
	while (chars_read != 0 && !ft_strchr1(txt, '\n'))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[chars_read] = '\0';
		temp = txt;
		txt = ft_strjoin1(txt, buffer);
		free(temp);
	}
	free(buffer);
	return (txt);
}

char	*get_line(char *txt)
{
	char	*line;
	int		line_len;
	int		i;

	line_len = 0;
	i = 0;
	if (!txt[0])
		return (NULL);
	while (txt[line_len] != '\n' && txt[line_len] != '\0')
		line_len++;
	if (txt[line_len] == '\n')
		line_len++;
	line = malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < line_len)
	{
		line[i] = txt[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*trimmed_txt(char *txt)
{
	char	*trimmed_txt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (txt[i] != '\n' && txt[i] != '\0')
		i++;
	if (!txt[i])
	{
		free(txt);
		return (NULL);
	}
	trimmed_txt = malloc((ft_strlen1(txt) - i + 1) * sizeof(char));
	if (!trimmed_txt)
		return (NULL);
	while (txt[i++])
		trimmed_txt[j++] = txt[i];
	trimmed_txt[j] = '\0';
	free(txt);
	return (trimmed_txt);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	txt = get_full_text(fd, txt);
	if (!txt)
		return (NULL);
	next_line = get_line(txt);
	txt = trimmed_txt(txt);
	return (next_line);
}
