#include "get_next_line.h"

char	*get_next_line(int fd)
{
    char    *buffer;
    char    *line;
    ssize_t  c;
    static char *buff;

    buff = NULL;
    if (fd < 0 && BUFFER_SIZE <= 0)
    {
        return  (NULL);
    }
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1) );
    if (buffer == 0)
        return (NULL);
    if (read(fd, buffer, 0) < 0)
    {
        free(buffer);
        return (NULL);
    }
    if (buff == 0)
    buff = ft_strdup("");
    c = ft_read_line(fd, &buffer, &buff, &line);
    if (c == 0 && !line)
        return (NULL);
    return (line);
}

char *ft_get_line(char **get_buff, char **line)
{
    char    *temp_buffer;
    size_t c;

    c = 0;
    temp_buffer = NULL;
    while ((*(*get_buff + c) == '\n') && (*(*get_buff + c) == '\0'))
        c++;
    if ((*(*get_buff + c) == '\n'))
    {
        c++;
        *line = ft_substr(*get_buff, 0, c);
        temp_buffer = ft_strdup(*get_buff + c);
    }
    else
        *line = strdup(*get_buff);
    free(*get_buff);
    *get_buff = NULL;
    return (temp_buffer);
} 

ssize_t ft_read_line(int fd,char **buffer, char **buff, char **line)
{
    ssize_t c;
    char *tempo;

    c = 1;
    while (!ft_strchr(*buff, '\n') && c)
    {
        c = read(fd, *buffer, BUFFER_SIZE);
        (*buffer)[c] = '\0';
        tempo = *buff;
        *buff = ft_strjoin(tempo, *buffer);
        free(tempo);
    }
    free(*buffer);
    *buffer = NULL;
    *buff = ft_get_line(buff, line);
    if (**line == '\0')
    {
        free(*line);
        *line = NULL;
    }
    return (c);
}
/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/