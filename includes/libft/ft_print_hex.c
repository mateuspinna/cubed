/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:06:05 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:29:15 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(long long int arg, char str)
{
	char	*hex;
	char	*hex_cap;
	int		digits;

	digits = countdigits_hex(arg);
	hex_cap = "0123456789ABCDEF";
	hex = "0123456789abcdef";
	if (arg > 15)
		ft_print_hex(arg / 16, str);
	if (str == 'x')
		ft_putchar(hex[arg % 16]);
	if (str == 'X')
		ft_putchar(hex_cap[arg % 16]);
	return (digits);
}
