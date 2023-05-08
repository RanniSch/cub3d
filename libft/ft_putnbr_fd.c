/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:02:59 by rschlott          #+#    #+#             */
/*   Updated: 2023/03/25 21:03:09 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//writes a number to a filedescriptor by converting it to ascii value
//so i can use write function to write them into filescriptor
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ui;

	if (n < 0)
	{
		write(fd, "-", 1);
		ui = (unsigned int)n * -1;
	}
	else
		ui = (unsigned int)n;
	if (ui >= 10)
		ft_putnbr_fd(ui / 10, fd);
	ui = ui % 10 + 48;
	write(fd, &ui, 1);
}
