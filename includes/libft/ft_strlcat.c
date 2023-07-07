/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:18:04 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/23 12:07:51 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = (ft_strlen(src));
	while (*dest && dstsize)
	{
		dest++;
		dstsize--;
		i++;
	}
	while (*src && dstsize > 1)
	{
		*dest++ = *src++;
		dstsize--;
	}
	if (dstsize)
		*dest = '\0';
	return (i + len);
}
