/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:14:47 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:33:19 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countdigits(long long int arg)
{
	int	digits;

	digits = 1;
	while (arg >= 10 || arg <= -10)
	{
		arg /= 10;
		digits++;
	}
	if (arg < 0)
		digits++;
	return (digits);
}
