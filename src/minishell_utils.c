/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:13:57 by mwilsch           #+#    #+#             */
/*   Updated: 2023/02/11 18:21:31 by mwilsch          ###   ########.fr       */
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
			printf("At %d char is %c\n", i, line[i]);
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
	while (line[i] && is_delimiter(line[i], delim_set)) // Skip over delim
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
	const int char_cnt = count_chars(line, delim_set, skip);
	printf("%d", char_cnt);
	return (NULL);
}

char **ft_split_ultimate(char *line, char *delim_set, char *skip)
{
	const int	wrd_cnt = count_wrds(line, delim_set, skip);
	char **str_arr;
	int i;

	printf("%s\n", line);
	printf("%d", wrd_cnt);
	
	// t_data sth = sth // Add a helper struct here
	// str_arr = malloc(sizeof(char *) * (wrd_cnt + 1));
	// if (!str_arr || wrd_cnt == -1)
	// 	return (free(str_arr), NULL);
	// str_arr[wrd_cnt] = NULL;
	// i = 0;
	// while (i < 1)
	// {
	// 	str_arr[i] = store_wrd(line, delim_set, skip);
	// 	// trim_string(line, delim_set, skip);
	// 	i++;
	// }

	return (NULL);
}

bool	is_quotes_closed(char *cmd_line_input)
{
	int	i;

	i = 0;
	while (cmd_line_input[i])
	{
	}
}

int main(int argc, char *argv[])
{
	char *cmd_line_input = readline(""); // Reading the cmd line input
	// char *cmd_line_input = argv[1];
	// char *delimt_set = " >|<";
	// char *skip = "\'\"";
	// 	// if (cmd_line_input[i] == '')
	// if (!is_quotes_closed(cmd_line_input)); // Is this okay?
	// 	return (1);
	// ft_split_ultimate(cmd_line_input, delimt_set, skip);
}
