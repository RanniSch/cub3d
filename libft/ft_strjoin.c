/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:04:31 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:04:41 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*concat;
	size_t		count;
	size_t		lenconcat;

	lenconcat = 0;
	count = 0;
	if (!s1)
		return (NULL);
	while (s1[count++] != '\0')
		lenconcat++;
	count = 0;
	while (s2[count++] != '\0')
		lenconcat++;
	concat = malloc(sizeof(char) * (lenconcat + 1));
	if (!concat)
		return (NULL);
	ft_memcpy(concat, s1, ft_strlen(s1));
	ft_memcpy(concat + ft_strlen(s1), s2, ft_strlen(s2));
	concat[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (concat);
}
