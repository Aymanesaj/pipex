/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asajed <asajed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:15:42 by asajed            #+#    #+#             */
/*   Updated: 2025/02/13 16:16:07 by asajed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	count_args(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		while (arg[i] == ' ')
			i++;
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] != '\'' && arg[i])
				i++;
			if (arg[i] == '\'')
				i++;
		}
		else
			while (arg[i] != ' ' && arg[i])
				i++;
		if (arg[i] != '\0' || (arg[i] == '\0' && arg[i - 1] != ' '))
			count++;
	}
	return (count);
}

char	*handle_single_quote(char *arg, int *i, int *start)
{
	char	*args;

	(*i)++;
	(*start) = (*i);
	while (arg[(*i)] != '\'' && arg[(*i)])
		(*i)++;
	args = ft_substr(arg, (*start), (*i) - (*start));
	if (!args)
		return (NULL);
	(*i)++;
	return (args);
}

char	*handle_spaces(char *arg, int *i, int *start)
{
	char	*args;

	*start = *i;
	while (arg[(*i)] != ' ' && arg[(*i)])
		(*i)++;
	args = ft_substr(arg, *start, (*i) - *start);
	if (!args)
		return (NULL);
	if (arg[(*i)] == ' ')
		(*i)++;
	return (args);
}

int	split_args(char *arg, char **args)
{
	int (i), (count), (start);
	i = 0;
	count = 0;
	start = 0;
	while (arg[i])
	{
		while (arg[i] == ' ')
			i++;
		if (arg[i] == '\'')
		{
			args[count] = handle_single_quote(arg, &i, &start);
			if (!args[count])
				return (ft_free(args), 0);
			count++;
		}
		else if (arg[i] != '\0')
		{
			args[count] = handle_spaces(arg, &i, &start);
			if (!args[count])
				return (ft_free(args), 0);
			count++;
		}
	}
	args[count] = NULL;
	return (1);
}

char	**tokenize_args(char *arg)
{
	char	**args;

	int (count);
	count = count_args(arg);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	if (!split_args(arg, args))
		return (NULL);
	return (args);
}
