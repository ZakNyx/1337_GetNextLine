/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihirri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:07:11 by zihirri           #+#    #+#             */
/*   Updated: 2021/11/28 18:45:01 by zihirri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char **buff, char **line)
{
	size_t	i;
	char	*second_buff;

	second_buff = NULL;
	i = 0;
	while ((*buff)[i] != '\n' && (*buff)[i] != '\0')
		i++;
	if ((*buff)[i] == '\n')
	{
		i++;
		*line = ft_substr(*buff, 0, i);
		second_buff = ft_strdup(*buff + i);
	}
	else
		*line = ft_strdup(*buff);
	free(*buff);
	*buff = NULL;
	return (second_buff);
}

ssize_t	ft_read_file(int fd, char *buffer, char **buff, char **line)
{
	char	*tempo;
	ssize_t	n;

	n = 1;
	while (ft_strchr(*buff, '\n') == 0 && n)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = '\0';
		tempo = *buff;
		*buff = ft_strjoin(tempo, buffer);
		free(tempo);
	}
	free(buffer);
	buffer = NULL;
	*buff = ft_get_line(buff, line);
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
	c = ft_read_file(fd, buffer, &buff[fd], &line);
	if (c == 0 && !line)
		return (NULL);
	return (line);
}
