/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:04:45 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:04:55 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	count = 0;
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	while (src[count] && dstsize > dstlen + count + 1)
	{
		dst[dstlen + count] = src[count];
		count++;
	}
	dst[count + dstlen] = '\0';
	return (srclen + dstlen);
}
