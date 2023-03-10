/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate_reference.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:26 by verdant           #+#    #+#             */
/*   Updated: 2023/03/01 12:32:31 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"


int	count_wrds(char *line, char *delim_set, char *skip)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (line == NULL)
		return (-1);
	// while (line[i] && is_delim(line[i], delim_set))
	// 	i++;
	while (line[i])
	{
		if (!is_delim(line[i], delim_set))
		{
			cnt++;
			while (!is_delim(line[i], delim_set))
				i++;
		}
		i++;
	}
	return (cnt);
}
// int	count_wrds(char *line, char *delim_set, char *skip)
// {
// 	int	i;
// 	int	cnt;

// 	i = 0;
// 	cnt = 0;
// 	if (line == NULL)
// 		return (-1);
// 	while (line[i])
// 	{
// 		// If it charcs a between a skip character delim don't count
// 		if (is_skip(line[i], skip))
// 		{
// 			i++;
// 			while (!is_skip(line[i], skip) && line[i + 1] != '\0')
// 				i++;
// 		}
// 		// If a word has been reached
// 		if (!is_delimiter(line[i], delim_set) && !is_skip(line[i], skip) && line[i + 1] != '\0')
// 		{
// 			cnt++;
// 			while (!is_delimiter(line[i], delim_set) && line[i + 1] != '\0')
// 				i++;
// 		}
// 	}
// 	return (cnt);
// }

// char **ft_split_ultimate_old(char *line, char *delim_set, char *)
{
	const int	wrd_cnt = count_wrds(line, delim_set, skip);

	// printf("%d\n", wrd_cnt);
	// char **str_arr;
	// int i;
	// char *line_trimable;
	
	// // t_data sth = sth // Add a helper struct here

	// line_trimable = ft_strdup(line);
	// str_arr = malloc(sizeof(char *) * (wrd_cnt + 1));
	// if (!str_arr || wrd_cnt == -1)
	// 	return (free(str_arr), NULL);
	// str_arr[wrd_cnt] = NULL;
	// i = 0;
	// while (i < wrd_cnt)
	// {
	// 	str_arr[i] = store_wrd(line_trimable, delim_set, skip);
	// 	// if (str_arr[i] == NULL) // Do we need this?
	// 		// free_mem(str_arr); 
	// 	trim_string(line_trimable, delim_set, skip);
	// 	i++;
	// }
	return (NULL);
}

