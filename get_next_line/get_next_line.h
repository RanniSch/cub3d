/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:53:55 by rschlott          #+#    #+#             */
/*   Updated: 2023/05/15 17:22:35 by mrehberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1

# include <fcntl.h> 
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>

int				ft_strlen_gnl(const char *c);
void			ft_bzero_gnl(void *s, size_t n);
void			*ft_calloc_gnl(size_t nmemb, size_t size);
char			*ft_strchr_gnl(char *s, int c);
size_t			ft_strlcat_gnl(char *dst, const char *s2, size_t len);
char			*get_next_line(int fd);

#endif