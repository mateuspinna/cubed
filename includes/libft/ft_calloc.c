/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:22:18 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/25 07:56:16 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem_address;
	size_t	total_size;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	total_size = count * size;
	mem_address = malloc(total_size);
	if (!mem_address)
		return (NULL);
	ft_bzero(mem_address, total_size);
	return (mem_address);
}
