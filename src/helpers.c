/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:50:03 by asajed            #+#    #+#             */
/*   Updated: 2025/02/14 23:40:31 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*z;

	i = 0;
	z = s;
	while (i < n)
	{
		z[i] = 0;
		i++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *) s1;
	s4 = (unsigned char *) s2;
	while (i < n && (s3[i] || s4[i]))
	{
		if (s3[i] > s4[i])
			return (1);
		else if (s3[i] < s4[i])
			return (-1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	len = i + j;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(str + i, s2, j);
	str[len] = '\0';
	return (str);
}
