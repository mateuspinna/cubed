/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:16 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/27 07:02:11 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_digits(int n)
{
	int			digits;
	long int	nbr;

	digits = 0;
	nbr = n;
	if (nbr <= 0)
	{
		nbr *= -1;
		digits++;
	}	
	while (nbr > 0)
	{	
		nbr /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int			digits;
	char		*ascii;
	long int	nbr;

	digits = ft_get_digits(n);
	nbr = n;
	if (n < 0)
		nbr *= -1;
	ascii = malloc((digits + 1) * sizeof(char));
	if (!ascii)
		return (NULL);
	ascii[digits] = '\0';
	while (digits)
	{
		ascii[--digits] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		ascii[0] = '-';
	return (ascii);
}
