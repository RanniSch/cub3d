/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:16:53 by rschlott          #+#    #+#             */
/*   Updated: 2023/04/07 17:27:30 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Read: attempts to read up to count bytes from file descriptor fd into the 
    buffer starting at buf. On success, the number of bytes read is returned 
    (zero indicates end of file), and the file position is advanced by this 
    number. If the file offset is at or past the end of file, no bytes are read, 
    and read() returns zero.
   GNL: returns one line until '\n' instead of the whole file. At the second
   	call from main it continues to return the second line and so on. */

static char	*ft_strjoin_gnl(char *s1, char *s2);
static char	*line_to_n(char *return_str, char *buf);
static char	*line_after_n(char *return_str, char *buf, char *str);
static char	*finished_reading(char *return_str, int bytes);

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*dst;
	int		len1;

	i = 0;
	len1 = ft_strlen_gnl(s1);
	len = len1 + ft_strlen_gnl(s2)+ 1;
	dst = ft_calloc(len, sizeof(char));
	while (i < (len1 + 1))
	{
		dst[i] = s1[i];
		i++;
	}
	ft_strlcat_gnl(dst, s2, len);
	ft_bzero(s2, ft_strlen_gnl(s2));
	if (s1)
		free (s1);
	return (dst);
}

static char	*line_to_n(char *return_str, char *buf)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	str = ft_calloc(ft_strlen_gnl(return_str) + 1, sizeof(char));
	if (return_str[0] == '\n')
		return (line_after_n(return_str, buf, str));
	while (return_str[i] != '\n')
	{
		str[i] = return_str[i];
		i++;
	}
	str[i] = '\n';
	i++;
	j = 0;
	while (return_str[j + i])
	{
		buf[j] = return_str[j + i];
		j++;
	}
	buf[j] = '\0';
	free (return_str);
	return (str);
}

static char	*line_after_n(char *return_str, char *buf, char *str)
{
	int	i;

	i = 0;
	while (return_str[i + 1])
	{
		buf[i] = return_str[i + 1];
		i++;
	}
	while (buf[i])
	{
		buf[i] = '\0';
		i++;
	}
	str[0] = '\n';
	str[1] = '\0';
	free (return_str);
	return (str);
}

static char	*finished_reading(char *return_str, int bytes)
{
	if (bytes < 0)
	{
		free (return_str);
		return (NULL);
	}
	if (bytes == 0)
	{	
		if (return_str[0])
			return (return_str);
		free (return_str);
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	int			bytes;
	char		*return_str;

	if (fd < 0 || fd > 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	return_str = ft_calloc(1, sizeof(char));
	bytes = 1;
	while (bytes)
	{
		if (buf[0] != '\0')
		{
			return_str = ft_strjoin_gnl(return_str, buf);
			if (ft_strchr_gnl(return_str, '\n'))
				return (line_to_n(return_str, buf));
		}
		bytes = read(fd, buf, BUFFER_SIZE);
		return_str = ft_strjoin_gnl(return_str, buf);
		if (bytes > 0 && ft_strchr_gnl(return_str, '\n'))
			return (line_to_n(return_str, buf));
		if (bytes <= 0)
			return (finished_reading(return_str, bytes));
	}
	return (return_str);
}
