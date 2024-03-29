/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zihirri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 21:07:34 by zihirri           #+#    #+#             */
/*   Updated: 2021/11/27 21:07:43 by zihirri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = (unsigned char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)(&s[i]));
		i++;
	}
	if (ch == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	count;

	if (!dst || !src)
		return (0);
	i = 0;
	count = 0;
	while (src[count] != '\0')
		count++;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ccat;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = 0;
	while (s1[len_s1] != '\0')
		len_s1++;
	len_s2 = 0;
	while (s2[len_s2] != '\0')
		len_s2++;
	ccat = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (ccat == NULL)
		return (NULL);
	ft_strlcpy(&ccat[0], s1, len_s1 + 1);
	ft_strlcpy(&ccat[len_s1], s2, len_s2 + 1);
	return (ccat);
}

char	*ft_strdup(const char *s1)
{
	size_t	size;
	size_t	i;
	char	*ptr;

	if (!s1)
		return (NULL);
	size = 0;
	while (s1[size] != '\0')
		size++;
	ptr = malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[size] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sstr;
	size_t	strlen;

	if (s == NULL)
		return (NULL);
	strlen = 0;
	while (s[strlen] != '\0')
		strlen++;
	if (start > strlen)
		return (ft_strdup(""));
	if (strlen - start >= len)
		sstr = (char *)malloc((len + 1) * sizeof(char));
	else
		sstr = (char *)malloc((strlen - start + 1) * sizeof(char));
	if (sstr == NULL)
		return (NULL);
	ft_strlcpy(sstr, (s + start), (len + 1));
	return (sstr);
}
