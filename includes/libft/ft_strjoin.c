/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:04:52 by mpinna-l          #+#    #+#             */
/*   Updated: 2022/05/26 11:26:11 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		s1s2_len;

	if (!s1)
		return (0);
	s1s2_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc((s1s2_len + 1) * sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	while (*s1)
		*joined_str++ = *s1++;
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	return (joined_str - s1s2_len);
}
