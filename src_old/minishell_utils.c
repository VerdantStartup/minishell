/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:13:57 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/04 12:11:32 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include <strings.h>

bool	is_delimiter(char c, char *delimiters)
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

bool	incl_char(char c, char *search_str)
{
	int	i;

	i = 0;
	if (!search_str)
		return (false);
	while (search_str[i])
	{
		if (c == search_str[i])
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
			cnt++;
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
		i++;
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

char	*ft_strdup(const char *source)
{
	int		size;
	char	*target;

	size = strlen(source) + 1;
	target = (char *)malloc(size * sizeof(char));
	if (target == NULL)
		return (NULL);
	strlcpy(target, (char *)source, size);
	return (target);
}

char **ft_split_ultimate(char *line, char *delim_set, char *skip)
{
	const int	wrd_cnt = count_wrds(line, delim_set, skip);
	char **str_arr;
	int i;
	char *line_trimable;
	
	// t_data sth = sth // Add a helper struct here

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

bool	are_quotes_even(char *cmd_line_input)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*target;
	int		i;

	if (!s1 && !s2)
		return (0);
	// if (!s1)
	// 	return (ft_strdup(s2));
	// if (!s2)
	// 	return (ft_strdup(s1));
	size = strlen(s1) + strlen(s2) + 1;
	target = (char *)malloc((size + 1) * sizeof(char));
	i = 0;
	if (target == NULL)
		return (NULL);
	strlcpy(target, (char *)s1, strlen(s1) + 1);
	strlcat(target, (char *)s2, size + 1);
	return (target);
}

char	*add_to_arr(char *string,char *string_to_add, int size)
{
	int	i;
	char	*temp;

	i = 0;
	// printf("%d %s\n",size,  string_to_add);
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp[size] = '\0';
	while (i < size)
	{
		temp[i] = string_to_add[i];
		i++;
	}
	free(string);
	return (temp);
}




// Single and multiple cmd resolution works but I need to figure out a way 
// that I only resolute if there is a pipe infront of the string

char	*cmd_resolution(char *arr)
{
	// 1. Get the PATH Environment Variable
	char *path_var = getenv("PATH");

	//	2. Split it every directory using : as delimiter
	char **path_modfiable = ft_split_ultimate(path_var, ":", NULL);
	
	
	int i_loop = 0;
	while (path_modfiable[i_loop] != NULL)
	{
		// Add the command we are looking for to the subdirectory
		path_modfiable[i_loop] = ft_strjoin(path_modfiable[i_loop], "/");
		path_modfiable[i_loop] = ft_strjoin(path_modfiable[i_loop], arr);
		// Check if executable exsits with access
		if (access(path_modfiable[i_loop], X_OK) == 0)
		{
			arr = add_to_arr(arr, path_modfiable[i_loop], strlen(path_modfiable[i_loop]));
			break;
		}
		i_loop++;
	}
	// free_split;
	return (arr);
}

// What if I do all the steps for each cmd invidually instead of resolute all cmds at once
// If I split without the pipe I know where the cmd and it's args stop regardsless if there
// is a space or not

// So in theory I will resolute the first command and handle everything else as arguments
// unless the I encounter a | which acts as flag that a  new commands has to be resoluted

	// while (arr[i] != NULL)
	// {
	// 	printf("%d\t%s\n",i ,arr[i]);
	// 	i++;
	// }



// void	argument_parsing(char **arr, char *line)
// {
// 	char **input_operators;
// 	char *skip = "\'\"";

// 	input_operators = ft_split_ultimate(line, " |", skip);
// 	for (int i = 0; arr[i] != NULL; i++)
// 		printf("%d\t%s\n",i ,arr[i]);
// 	write(1, "\n", 1);
// 	for (int i = 0; input_operators[i] != NULL; i++)
// 		printf("%d\t%s\n",i ,input_operators[i]);




	
// }

// What is there to parse?
	// 1. Env Vars
	// 2. If the file exsits or not
	// flags and options don't need to be evaluated

// Question is
	//





bool has_pipe(char *str)
{
	int i = 0;
	
	while(str[i])
	{
		if (str[i] == '|')
			return(true);
		i++;
	}
	return (false);
}

char *trim_for_pipe(char *line)
{
	int	i = 0;
	int	k = 0;

	while (line[i] && line[i] != '|')
		i++;
	i++;
	while (line[i])
		line[k++] = line[i++];
	line[k] = '\0';
	printf("%s\n", line);
	return (line);
}

int main(int argc, char *argv[])
{
	char *cmd_line_input = readline(""); // Reading the cmd line input
	char *delimt_set = " <>";
	char *skip = "\'\"";
	
	if (!are_quotes_even(cmd_line_input)) // Is this okay?
		return (1);

	char **arr = ft_split_ultimate(cmd_line_input, delimt_set, skip);
	
	int i = 0;
	while (arr[i])
	{
		if  (i == 0)
			arr[i] = cmd_resolution(arr[i]);
		if (has_pipe(arr[i]))
			arr[i] = cmd_resolution(trim_for_pipe(arr[i]));
		i++;
	}
	
	// for (i = 0; arr[i] != NULL; i++)
	// 	printf("%d\t%s\n",i ,arr[i]);





	// char **test = ft_split_ultimate(cmd_line_input, " |", skip);
	// for (i = 0; test[i] != NULL; i++)
	// 	printf("%d\t%s\n",i ,test[i]);
	// argument_parsing(arr, cmd_line_input);
	// while (arr[i] != NULL)
	// {
	// 	printf("%d\t%s\n",i ,arr[i]);
	// 	i++;
	// }
	return (0);
}


// 1. Search input string for |
// 2. malloc string to search and 
// 3. then strnstr string to search in arr

// Problem solved
// 1. I use ft_split_ultimate for checking
// 2.0 Split again only on spaces
// 2. char **argv[0] = cmd
// 3. the whole argv is the 2nd argument for execve
// 4. if a operator occurs count the occurences and everything after (including) operator goes into it's own string
// Done.

// What if I build a functin that firstly checks for what operations there are in a string
// Then let's say we have a >> and a |
	// I would have a arr where each index corresspondes to a operation 
	// Then I set the occurences to true and anything else to false
	// Then for the occurences I check for counts
		// >>> is incorrect
		// << 

		// >>, >
		// <<, <
		// |
	
	// Check for occurences of operators
	// Anything which occures set to true
	// The occurces then decide which if clauses to check