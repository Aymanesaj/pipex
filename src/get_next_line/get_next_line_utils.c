/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:43:55 by asajed            #+#    #+#             */
/*   Updated: 2025/01/28 16:46:42 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;

	dst = (unsigned char *)b;
	while (len--)
	{
		*dst = (unsigned char) c;
		dst++;
	}
	return (b);
}

size_t	lenght(char *s, char *till_newline)
{
	size_t	i;

	i = 0;
	if (!s && !till_newline)
		return (-1);
	if (till_newline && !s)
	{
		while (till_newline[i] != '\n' && till_newline[i])
			i++;
		if (till_newline[i] == '\n')
			i++;
	}
	if (s && !till_newline)
	{
		while (s[i])
			i++;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*to_dst;
	const unsigned char	*to_src;

	to_dst = (unsigned char *)dst;
	to_src = (const unsigned char *)src;
	if (to_dst == to_src || !n)
		return (dst);
	i = 0;
	if (to_dst == to_src || !n)
		return (dst);
	while (i < n)
	{
		to_dst[i] = to_src[i];
		i++;
	}
	return (dst);
}

char	*substr(char const *s, unsigned int start, size_t len)
{
	char	*v;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = 0;
	i = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return (malloc(1));
	if (len > s_len - start)
		len = s_len - start;
	v = (char *)malloc(len + 1);
	if (!v)
		return (NULL);
	while (i < len && s[start])
	{
		v[i] = s[start];
		i++;
		start++;
	}
	v[i] = '\0';
	return (v);
}

char	*ft_nstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	i = lenght(s1, NULL);
	j = lenght(s2, NULL);
	str = (char *)malloc(i + j + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(str + i, s2, j);
	str[i + j] = '\0';
	free(s1);
	free(s2);
	return (str);
}
