/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:03:50 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:03:52 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	length;

	length = 0;
	while (s[length])
	{
		if (s[length] == (char)c)
			return ((char *)s + length);
		length++;
	}
	if (s[length] == (char)c)
		return ((char *)s + length);
	return (NULL);
}
