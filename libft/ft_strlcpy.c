/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:04:59 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:05:08 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (!dstsize)
		return (srclen);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = *((char *)src + i);
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (srclen);
}
