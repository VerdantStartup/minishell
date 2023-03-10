/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ultimate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:06:26 by verdant           #+#    #+#             */
/*   Updated: 2023/03/10 12:56:02 by verdant          ###   ########.fr       */
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
 		if (incl_char(line[i], skip))
 		{
 			cnt++;
 			i++;
 			while (!incl_char(line[i], skip) && line[i + 1] != '\0')
				i++;
		}
		// If a word has been reached
		if (!incl_char(line[i], delim_set) && !incl_char(line[i], skip) && line[i + 1] != '\0')
		{
			cnt++;
			while (!incl_char(line[i], delim_set) && line[i + 1] != '\0')
				i++;
		}
		i++;
	}
	return (cnt);
}


char **ft_split_ultimate(char *line, char *delim_set, char *skip)
 {
 	const int	wrd_cnt = count_wrds(line, delim_set, skip);
 	char			**str_arr;
 	int				i;

 	// printf("%s\n", line);
 	// printf("%d", wrd_cnt);

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


