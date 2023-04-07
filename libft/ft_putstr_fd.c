/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:03:13 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:03:23 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// writes length of string to filescriptor
void	ft_putstr_fd(char *s, int fd)
{
	size_t	length;

	if (s)
	{
		length = ft_strlen(s);
		write(fd, s, length);
	}
}
