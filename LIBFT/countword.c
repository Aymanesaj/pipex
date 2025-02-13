/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countword.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:21:36 by asajed            #+#    #+#             */
/*   Updated: 2025/02/13 14:21:12 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	single_quote(const char *s, int *start, int *i)
{
	int (j);
	j = *i;
	if (s[(*i)] != 39 || !s[(*i)])
		return (-1);
	j++;
	*start += 1;
	while (s[j] && s[j] != 39)
		j++;
	if (s[j] != 39)
		return (-1);
	*i = j;
	(*i)++;
	return ((*i));
}

int	countword(char const *s, char c)
{
	int (i), (j), (l);
	i = 0;
	j = 0;
	l = 0;
	if (!s)
		return (0);
	while (s[i] == c && c != '\0')
		i++;
	while (s[i])
	{
		if (single_quote(s, &l, &i) != -1)
			j++;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}
