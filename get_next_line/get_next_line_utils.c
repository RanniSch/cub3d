/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:24:33 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/22 14:08:19 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

void	ft_bzero_gnl(void *s, size_t n)
{
	size_t	i;
	char	*p;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb >= __SIZE_MAX__ || size >= __SIZE_MAX__)
		return (0);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero_gnl(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strchr_gnl(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcat_gnl(char *dst, const char *s2, size_t len)
{
	size_t	len2;
	size_t	dst_len;
	size_t	i;

	len2 = ft_strlen_gnl(s2);
	if (len == 0)
		return (len2);
	dst_len = 0;
	while (dst_len < len && dst[dst_len])
		dst_len++;
	if (len <= dst_len)
		return (len + len2);
	i = 0;
	while (len && (--len - dst_len > 0) && s2[i])
	{
		dst[dst_len + i] = s2[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (len2 + dst_len);
}
