/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:04:42 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:29:40 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_pointer(unsigned long long arg)
{
	if (arg > 15)
		ft_putnbr_pointer(arg / 16);
	ft_putchar("0123456789abcdef"[arg % 16]);
}

int	ft_print_pointer(unsigned long long arg)
{
	int	c;

	ft_putchar('0');
	ft_putchar('x');
	ft_putnbr_pointer(arg);
	c = countdigits_ull(arg);
	return (c);
}
