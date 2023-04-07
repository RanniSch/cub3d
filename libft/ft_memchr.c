/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:59:53 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:00:14 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* From manual: The  memchr()  function scans the initial n 
bytes of the memory area
 pointed to by s for the first instance ofc.  Both c and the bytes of 
 the memory area pointed to by s are interpreted as unsigned char.
The  memchr()  and memrchr() functions return a pointer to the
 matching byte or NULL if the character does not
occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
