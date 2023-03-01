/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:25 by verdant           #+#    #+#             */
/*   Updated: 2023/02/28 16:43:48 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

bool	is_quotes_closed(char *input)
{
	int	i;
	int	cnt;
	int	cnt2;

	i = 0;
	cnt = 0;
	cnt2 = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			cnt++;
		if (input[i] == '\"')
			cnt2++;
		i++;
	}
	if (cnt == 2 || cnt2 == 2 || cnt == 0 || cnt2 == 0)
		return (true);
	return (false);
}

bool	is_delim(char c, char *delimiters)
{
	int	i;

	i = 0;
	if (!delimiters)
		return (false);
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (true);
		i++;
	}
	return (false);
}

int count_occurences(char *input, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 1;
	while(input[i])
	{
		if (input[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}

void	free_split(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

bool	is_skip(char c, char *skip)
{
	int	i;

	i = 0;
	if (!skip)
		return (false);
	while (skip[i])
	{
		if (c == skip[i])
			return (true);
		i++;
	}
	return (false);
}