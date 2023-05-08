/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:56:44 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 20:56:53 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_length(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = count_length(n);
	array = malloc(sizeof(char) * i + 1);
	if (!array)
		return (NULL);
	ft_bzero(array, i + 1);
	if (n < 0)
	{
		array[0] = '-';
		n = n * -1;
	}
	while (n > 9)
	{
		array[i - 1] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	array[i - 1] = (n % 10) + '0';
	return (array);
}
