/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:59:39 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 20:59:48 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function name ft_lstsize
Prototype int ft_lstsize(t_list *lst);
Turn in files -
Parameters lst: The beginning of the list.
Return value The length of the list
External functs. None
Description Counts the number of nodes in a list. */
int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	if (!lst)
		return (0);
	temp = lst;
	i = 1;
	while (temp->next)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
