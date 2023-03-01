/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:26 by verdant           #+#    #+#             */
/*   Updated: 2023/03/01 15:16:22 by verdant          ###   ########.fr       */
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
	char *delim_set = ft_strjoin(delim_skip, delim_keep);
	while (line[i])
	{
		// Reached a non-delimiter character = Reached a word
		if (!is_delim(line[i], delim_set))
		{
			cnt++;
			while (!is_delim(line[i], delim_set) && line[i + 1] != '\0')
				i++;
		}
		i++; // Skip over delimiters
	}
	return (cnt);
}

char **ft_split_ultimate(char *line, char *delim_skip, char *delim_keep, char *keep)
{
	const int	wrd_cnt = count_wrds(line, delim_skip, delim_keep, keep);
	printf("%d", wrd_cnt);
	return (NULL);
}


