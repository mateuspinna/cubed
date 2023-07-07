/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:53:21 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/17 11:41:05 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char const *set)
{
	while (*set && c != *set)
		set++;
	if (c == *set)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	end;

	if (!s1)
		return (NULL);
	while (*s1 && is_charset(*s1, set))
		s1++;
	end = ft_strlen(s1);
	while (end && is_charset(s1[end], set))
		end--;
	return (ft_substr(s1, 0, end + 1));
}
