/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:53:55 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/07 16:41:38 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sign;
	int			count;
	long int	number;

	count = 0;
	sign = 1;
	while (str[count] == 32 || (str[count] <= 13 && str[count] >= 9))
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
				sign = -1;
		count++;
	}
	number = 0;
	while (str[count] != '\0' && str[count] <= '9' && str[count] >= '0')
	{
		if (number > 2147483648 && sign == -1)
			return (0);
		if (number > 2147483647 && sign == 1)
			return (-1);
		number = number * 10 + (str[count] - '0');
		count++;
	}
	return (sign * number);
}
