/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:26 by verdant           #+#    #+#             */
/*   Updated: 2023/03/01 12:37:21 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

// echo -n “$HOME and more text”> output.txt

int	count_wrds(char *line, char *delim_skip, char *delim_keep, char *keep)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (line == NULL)
		return (-1);
	while (line[i])
	{
		// Reached a non-delimiter character = Reached a word
		if (!is_delim(line[i], delim_skip) || !is_delim(line[i], delim_keep))
		{
			cnt++;
			while (!is_delim(line[i], delim_skip) || !is_delim(line[i], delim_keep))
				i++;
		}
		i++; // Skip over delimiters
	}
	return (cnt);
}
// int	count_wrds(char *line, char *delim_skip, char *delim_keep, char *keep)
// {
// 	int	i;
// 	int	cnt;

// 	i = 0;
// 	cnt = 0;
// 	if (line == NULL)
// 		return (-1);
// 	while (line[i])
// 	{
// 		// Reached a "keep-char" everything inbetween should be skipped over
// 		if (is_skip(line[i], keep))
// 		{
// 			i++;
// 			while (!is_skip(line[i], keep))
// 				i++;
// 			// i++;
// 		}
// 		// Reached a non-delimiter character = Reached a word
// 		if (!is_delim(line[i], delim_skip) || !is_delim(line[i], delim_keep))
// 		{
// 			cnt++;
// 			while (!is_delim(line[i], delim_skip) || !is_delim(line[i], delim_keep))
// 				i++;
// 		}
// 		i++; // Skip over delimiters
// 	}
// 	return (cnt);
// }

char **ft_split_ultimate(char *line, char *delim_skip, char *delim_keep, char *keep)
{
	const int	wrd_cnt = count_wrds(line, delim_skip, delim_keep, keep);
	printf("%d", wrd_cnt);
	return (NULL);
}


