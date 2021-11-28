/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihirri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:07:11 by zihirri           #+#    #+#             */
/*   Updated: 2021/11/27 21:07:15 by zihirri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char **buff_read, char **line)
{
	size_t	i;
	char	*new_buff;

	i = 0;
	new_buff = NULL;
	while ((*(*buff_read + i) != '\n') && (*(*buff_read + i) != '\0'))
		i++;
	if (*(*buff_read + i) == '\n')
	{
		i++;
		*line = ft_substr(*buff_read, 0, i);
		new_buff = ft_strdup(*buff_read + i);
	}
	else
		*line = ft_strdup(*buff_read);
	free(*buff_read);
	*buff_read = NULL;
	return (new_buff);
}

ssize_t	ft_read_file(int fd, char **buffer, char **buff_read, char **line)
{
	char	*tempo;
	ssize_t	n;

	n = 1;
	while (!ft_strchr(*buff_read, '\n') && n)
	{
		n = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[n] = '\0';
		tempo = *buff_read;
		*buff_read = ft_strjoin(tempo, *buffer);
		free(tempo);
	}
	free(*buffer);
	*buffer = NULL;
	*buff_read = ft_get_line(buff_read, line);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
	}
	return (n);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*buffer;
	char		*line;
	ssize_t		c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!buff[fd])
		buff[fd] = ft_strdup("");
	c = ft_read_file(fd, &buffer, &buff[fd], &line);
	if (c == 0 && !line)
		return (NULL);
	return (line);
}
