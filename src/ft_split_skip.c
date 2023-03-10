/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_skip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:41:42 by verdant           #+#    #+#             */
/*   Updated: 2023/03/10 12:59:14 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_wrds(char *line, char *delim_set, char *skip)
{
	int	i;
	int	cnt;
	
	i = 0;
	cnt = 0;
	if (line == NULL)
		return (-1);
	while (line[i])
	{
		// If it charcs a between a skip character delim don't count
		if (is_skip(line[i], skip))
		{
			i++;
			while (!is_skip(line[i], skip) && line[i + 1] != '\0')
				i++;
		}
		// If a word has been reached
		if (!is_delimiter(line[i], delim_set) && !is_skip(line[i], skip) && line[i + 1] != '\0')
		{
			cnt++;
			while (!is_delimiter(line[i], delim_set) && line[i + 1] != '\0')
				i++;
		}
	}
	return (cnt);
}


int	count_chars(char *line, char *delim_set, char *skip)
{
	int	cnt;
	int	i;

 	cnt = 0;
 	i = 0;
 	if (!line)
 		return (-1);
 	// // Skip over delimiters
 	while (line[i] && incl_char(line[i], delim_set)) 
 		i++;
 	if (incl_char(line[i], skip)) // cnt chars until next skip char
 	{
		i++;
		while (line[i] && !is_skip(line[i], skip))
		{
			i++;
			cnt++;
		}
		return (cnt);
	}
	// cnt chars until next delimiter
	while (line[i] && !is_delimiter(line[i], delim_set))
	{
		i++;
		cnt++;
	}
	return (cnt);
}

char *store_wrd(char *line, char *delim_set, char *skip)
{
 	int	i;
 	int	k;
 	const int char_cnt = count_chars(line, delim_set, skip);
 	printf("%d", char_cnt);
 	return (NULL);
 	// printf("Char cnt = %d\n", char_cnt);

 	char *temp;

 	i = 0;
 	k = 0;
 	temp = malloc(sizeof(char) * (char_cnt + 1));
 	if (!temp || char_cnt == -1)
 		return (NULL);

 	temp[char_cnt] = '\0';
 	// Skipping over delimiters and skips chars
 	while (line[i] && (is_delimiter(line[i], delim_set) || is_skip(line[i], skip)))
 		i++;
 	// Copying the chars over
 	while (line[i] && k < char_cnt)
 		temp[k++] = line[i++];
 	return (temp);
}

void	trim_string(char *line, char *delimiters, char *skip)
{
 	int	i;
 	int	k;

 	i = 0;
 	k = 0;

 	while (line[i] && (incl_char(line[i], delimiters) || incl_char(line[i], skip)))
 		i++;
 	i += count_chars(line, delimiters, skip);
 		i++;
 	while (line[i] && incl_char(line[i], delimiters))
 		i++;
 	while (line[i])
 		line[k++] = line[i++];
 	line[k] = '\0';
}

 char **ft_split_ultimate(char *line, char *delim_set, char *skip)
 {
 	const int	wrd_cnt = count_wrds(line, delim_set, skip);
 	char	**str_arr;
 	int		i;
 	char *line_trimable;


 	line_trimable = ft_strdup(line);
 	str_arr = malloc(sizeof(char *) * (wrd_cnt + 1));
 	if (!str_arr || wrd_cnt == -1)
 		return (free(str_arr), NULL);
 	str_arr[wrd_cnt] = NULL;
 	i = 0;
 	while (i < wrd_cnt)
 	{
 		str_arr[i] = store_wrd(line_trimable, delim_set, skip);
 		// if (str_arr[i] == NULL) // Do we need this?
 			// free_mem(str_arr);
 		trim_string(line_trimable, delim_set, skip);
 		i++;
 	}
 	return (str_arr);
}