/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:36:48 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:30:54 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		str_len;

	str_len = 0;
	va_start(arg, str);
	i = 0;
	if (!*str)
		return (0);
	while (str[str_len])
		str_len++;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] != 0)
				placeholders(&str_len, str[i++], arg);
		}
		if (str[i] != '%' && str[i])
			ft_putchar(str[i++]);
	}
	va_end(arg);
	return (str_len);
}

void	placeholders(int *str_len, char str, va_list arg)
{
	if (str == 'i' || str == 'd')
		*str_len += (ft_print_decimal(va_arg(arg, int)) - 2);
	if (str == 'c')
		*str_len += (ft_putchar(va_arg(arg, int)) - 2);
	if (str == 's')
		*str_len += (ft_putstr(va_arg(arg, char *)) - 2);
	if (str == 'u')
		*str_len += (ft_print_uns_decimal(va_arg(arg, unsigned int)) - 2);
	if (str == '%')
		*str_len += (ft_putchar('%') - 2);
	if (str == 'x' || str == 'X')
		*str_len += (ft_print_hex(va_arg(arg, unsigned int), str) - 2);
	if (str == 'p')
		*str_len += ft_print_pointer(va_arg(arg, unsigned long long));
}
