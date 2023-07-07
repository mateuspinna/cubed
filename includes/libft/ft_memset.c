/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:41:36 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/16 11:38:37 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	converted_value;
	char			*temp;
	size_t			i;

	temp = (char *)b;
	i = 0;
	converted_value = c;
	while (len-- > 0)
		temp[i++] = converted_value;
	return (temp);
}
