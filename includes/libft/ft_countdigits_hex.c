/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigits_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:13:45 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:33:34 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countdigits_hex(long long arg)
{
	int	digits;

	digits = 1;
	while (arg > 15)
	{
		arg /= 16;
		digits++;
	}
	return (digits);
}
