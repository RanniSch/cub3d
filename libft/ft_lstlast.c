/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:58:39 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 20:58:50 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function name ft_lstlast
Prototype t_list *ft_lstlast(t_list *lst);
Turn in files -
Parameters lst: The beginning of the list.
Return value Last node of the list
External functs. None
Description Returns the last node of the list.
 */
t_list	*ft_lstlast(t_list *lst)
{
	int		i;
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	i = 0;
	while (temp->next)
	{
		i++;
		temp = temp->next;
	}
	return (temp);
}
