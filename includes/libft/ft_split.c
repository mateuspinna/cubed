/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:24:12 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/26 11:22:47 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char *str, char charset)
{	
	if (*str == charset)
		return (1);
	return (0);
}

static int	ft_counters(char *str, char charset, int flag)
{
	int	words;
	int	i;

	if (flag == 1)
	{
		i = 0;
		while (str[i] && !ft_is_charset(str + i, charset))
			i++;
		return (i);
	}
	words = 0;
	while (*str)
	{	
		while (*str && ft_is_charset(str, charset))
			str++;
		i = ft_counters(str, charset, 1);
		str = str + i;
		if (i)
			words++;
	}		
	return (words);
}

static char	*ft_copy(char *src, int wordlen)
{
	char	*dest;

	dest = malloc((wordlen + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[wordlen] = '\0';
	while (wordlen--)
		dest[wordlen] = src[wordlen];
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	char	**char_array;
	int		size;
	int		chars;
	int		i;

	if (!s)
		return (NULL);
	size = ft_counters((char *)s, c, 2);
	char_array = malloc((size + 1) * sizeof(char *));
	if (!char_array)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*s && ft_is_charset((char *)s, c))
			s++;
		chars = ft_counters((char *)s, c, 1);
		char_array[i] = ft_copy((char *)s, chars);
		if (!char_array)
			return (NULL);
		s += chars;
	}
	char_array[size] = 0;
	return (char_array);
}
