/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits_ull.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:12:18 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:33:50 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countdigits_ull(unsigned long long arg)
{
	int	digits;

	digits = 0;
	if (arg <= 0)
	{
		digits++;
		arg *= -1;
	}
	while (arg > 0)
	{
		arg /= 16;
		digits++;
	}
	return (digits);
}
