/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:00:47 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:00:56 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dstr;
	unsigned char	*srcr;

	dstr = (unsigned char *)dst;
	srcr = (unsigned char *)src;
	if (!n || (!dst && !src && n > 0))
		return (dstr);
	i = 0;
	while (i < n)
	{
		dstr[i] = srcr[i];
		i++;
	}
	return (dstr);
}
