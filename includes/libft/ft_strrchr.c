/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:13:45 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/25 07:52:03 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		len;
	const char	*start;

	start = s;
	c = c % 256;
	len = ft_strlen(s);
	s += len;
	while (s != start && *s != c)
		s--;
	if (*s == c)
		return ((char *) s);
	return (0);
}
