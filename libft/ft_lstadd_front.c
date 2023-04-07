/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:57:26 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 20:57:36 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//adds node to the end of a linked list
/* Parameters lst: The address of a pointer to the first link of
a list.
new: The address of a pointer to the node to be
added to the list.
Return value None
External functs. None
Description Adds the node ’new’ at the beginning of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{	
	if (new && lst)
	{
		new->next = lst[0];
		lst[0] = new;
	}
}
