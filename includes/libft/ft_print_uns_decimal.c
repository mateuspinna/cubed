/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_decimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:03:33 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:30:07 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_uns_decimal(unsigned int arg)
{
	long int	nbr;

	nbr = arg;
	if (nbr > 9)
		ft_print_uns_decimal(nbr / 10);
	ft_putchar(nbr % 10 + '0');
	return (countdigits(arg));
}
