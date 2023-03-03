/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:25 by verdant           #+#    #+#             */
/*   Updated: 2023/03/03 14:14:25 by mwilsch          ###   ########.fr       */
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
	cnt = 0;
	if (!input)
		return (-1);
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

void	err_msg(char *msg)
{
	printf("%s", msg);
}

int	ft_search_c(char *str, char c, char skip)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == skip) // Could be it's own int function i += skip()
		{
			i++;
			while (str[i] != skip && str[i + 1] != '\0')
				i++;
		}
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	count_occurences_skip(char *str, char c, char skip) // what if skip is nothing?
{
	int	i;
	int	cnt;
	
	i = 0;
	cnt = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == skip) // Could be it's own int function i += skip()
		{
			i++;
			while (str[i] != skip && str[i + 1] != '\0')
				i++;
		}
		if (str[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}



// int	ft_find_occur(char *str, char c, int occur)
// {
// 	int	i;
// 	int	cnt;
// 	static int d;

// 	i = 0;
// 	cnt = 0;
// 	// printf("In find at %d:\n%s\n", d, str);
// 	d++;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			cnt++;
// 		if (cnt == occur)
// 			return (i);
// 		i++;
// 	}
// 	return (-1); // Char at occurence not found
// }

// Assuming the quotes are always closed 
// bc I have a extra check for that in my main

// bool str_literal(char *str, int occur)
// {
// 	const int	dollar_at = ft_find_occur(str, '$', occur + 1);
// 	static int open = 1;
// 	// static int closed = 2;
// 	int	quote_open;
// 	// int	quote_clos;
	
// 	quote_open = ft_find_occur(str, '\'', open);
// 	// quote_clos = ft_find_occur(str, '\'', closed);
// 	open += 2;
// 	// closed += 2;

// 	// printf("O: %d C: %d Dol: %d\n", quote_open, quote_clos, dollar_at);
// 	if (quote_open == -1)
// 		return (false);
// 	// If dollar_at (index of $) is bigger then quote_open (index of opening ')
// 	// then the dollar is inside of a string literal
// 	return (dollar_at > quote_open);
// }
// bool str_literal(char *str)
// {
// 	// static int	dollar;
// 	// const int	quote_1 = ft
// 	// const int	quote_2 = ft

// '$PATH'

// 	// if (dollar == 0)
// 	// 	dollar = ft_strclen(str, '$');
// 	// else
// 	// 	dollar = ft_strclen(str + dollar + 1, '$');
	
// 	// printf("Dollar is at %d\tQuote is at %d\n", dollar, quote);
// 	printf("%d\n", ft_find_at(str, '$', 2));
// 	// return (dollar > quote);
// 	return (true);
// }

// -n '$PATH' "$HOME"