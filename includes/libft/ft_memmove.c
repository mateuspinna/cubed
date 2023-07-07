/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 08:20:15 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/26 11:24:36 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*converted_src;
	char	*converted_dst;
	size_t	i;

	converted_src = (char *)src;
	converted_dst = dst;
	if (dst == src || len == 0)
		return (dst);
	if (dst > src)
	{
		i = len;
		while ((int)--i >= 0)
			converted_dst[i] = converted_src[i];
		return (converted_dst);
	}
	if (dst < src)
	{
		i = -1;
		while (++i < len)
			converted_dst[i] = converted_src[i];
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
