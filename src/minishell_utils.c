/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:13:57 by mwilsch           #+#    #+#             */
/*   Updated: 2023/02/15 11:22:04 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

bool	is_delimiter(char c, char *delimiters)
{
	int	i;

	i = 0;
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_skip(char c, char *skip)
{
	int	i;

	i = 0;
	while (skip[i])
	{
		if (c == skip[i])
			return (true);
		i++;
	}
	return (false);
}



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
			// printf("At %d char is %c\n", i, line[i]);
			cnt++;
			i++;
			while (!is_skip(line[i], skip) && line[i + 1] != '\0')
				i++;
		}
		// If a word has been reached
		if (!is_delimiter(line[i], delim_set) && !is_skip(line[i], skip) && line[i + 1] != '\0')
		{
			// printf("At %d char is %c\n", i, line[i]);
			cnt++;
			while (!is_delimiter(line[i], delim_set) && line[i + 1] != '\0')
				i++;
		}
		i++;
	}
	// printf("%d", cnt);
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
	while (line[i] && is_delimiter(line[i], delim_set)) 
		i++;
	if (is_skip(line[i], skip)) // cnt chars until next skip char
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

	while (line[i] && (is_delimiter(line[i], delimiters) || is_skip(line[i], skip)))
		i++;
	i += count_chars(line, delimiters, skip);
		i++;
	while (line[i] && is_delimiter(line[i], delimiters))
		i++;
	while (line[i])
		line[k++] = line[i++];
	line[k] = '\0';
}

void	free_mem

char **ft_split_ultimate(char *line, char *delim_set, char *skip)
{
	const int	wrd_cnt = count_wrds(line, delim_set, skip);
	char **str_arr;
	int i;
	
	// t_data sth = sth // Add a helper struct here
	str_arr = malloc(sizeof(char *) * (wrd_cnt + 1));
	if (!str_arr || wrd_cnt == -1)
		return (free(str_arr), NULL);
	str_arr[wrd_cnt] = NULL;
	i = 0;
	while (i < wrd_cnt)
	{
		str_arr[i] = store_wrd(line, delim_set, skip);
		// if (str_arr[i] == NULL) // Do we need this?
			// free_mem(str_arr); 
		trim_string(line, delim_set, skip);
		i++;
	}
	return (str_arr);
}

bool	is_quotes_closed(char *cmd_line_input)
{
	int	i;
	int	cnt;
	int	cnt2;

	i = 0;
	cnt = 0;
	cnt2 = 0;
	while (cmd_line_input[i])
	{
		if (cmd_line_input[i] == '\'')
			cnt++;
		if (cmd_line_input[i] == '\"')
			cnt2++;
		i++;
	}
	if (cnt == 2 || cnt2 == 2 || cnt == 0 || cnt2 == 0)
		return (true);
	return (false);
}

int main(int argc, char *argv[])
{
	char *cmd_line_input = readline(""); // Reading the cmd line input
	char *delimt_set = " >|<";
	char *skip = "\'\"";
	if (!is_quotes_closed(cmd_line_input)) // Is this okay?
		return (1);
	char **arr = ft_split_ultimate(cmd_line_input, delimt_set, skip);
	int i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
	return (0);
}
