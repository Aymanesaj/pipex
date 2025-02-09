/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:43:55 by asajed            #+#    #+#             */
/*   Updated: 2024/10/29 17:42:55 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*str;

	if (!s || !f)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char	ft(unsigned int i, char c)
// {
// 	(void *)i;
// 	return (c + 32);
// }
// #include <stdio.h>

// int main() 
// {
// 	char s[] = "AYMANE";
// 	char (*f) (unsigned int, char);
// 	f =  &ft;
// 	printf("%s",ft_strmapi(s, f));
// }