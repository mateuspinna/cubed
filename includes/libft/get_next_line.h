/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:59:53 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/12 15:58:16 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 29
# endif

char	*get_next_line(int fd);
char	*ft_strchr1(const char *s, int c);
char	*ft_strjoin1(char *s1, char *s2);
size_t	ft_strlen1(char *str);

#endif
