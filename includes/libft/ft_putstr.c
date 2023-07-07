/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:57:46 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/07/28 15:31:53 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	char	*str2;

	str2 = str;
	if (str == 0)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*str)
		ft_putchar(*str++);
	return (str - str2);
}
