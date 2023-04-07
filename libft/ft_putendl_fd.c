/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:02:43 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:02:55 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//writes a string to a filedescriptor
void	ft_putendl_fd(char *s, int fd)
{
	size_t	length;

	if (s)
	{
		length = ft_strlen(s);
		write(fd, s, length);
		write(fd, "\n", 1);
	}
}
