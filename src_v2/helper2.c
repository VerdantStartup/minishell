/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:46:00 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/08 13:26:37 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

/**
 * @brief Deletes a substr from a str
 * 
 * @param start The starting index of str to delete from
 * @param len The amount of chars to delete
 * 
 * @note I could rewrite this function to be a bool and use a double ptr
 * for char *str so that I do not lose the changes outside local scope, however
 * this would entail that I have to rewrite my env_subsitution to accomodate
 * for that
 * 
 * @note Benefits: 1. I can check if del_substr went right or not 2. I can 
 * save lines
*/
char	*del_substr(char *str, int start, int len)
{
	int	copy_from;

	if (!str)
		return (NULL);
	if (len == 0)
		return (str);
	copy_from = start + len;
	while (str[copy_from])
		str[start++] = str[copy_from++];
	str[start] = '\0';
	return (str);
}


/**
 * @brief display error messages
 * 
 * @param err_token defines which error it is
 * 
 * @note I need to find a way to pass the right character such as > or >> as a 
 * error and so on
 * 
 * tomorrrow, bruh
*/
bool error_syntax(char *str, t_err_token err_tok)
{
	// it would be better is I use write to write to std error
	
	if (err_tok == TOO_MANY)
		ft_printf("minishell: To many redirects\n"); 
	if (err_tok == NO_ALNUM_1)
		ft_printf("minishell: NO ALNUM value between redirect\n");
	if (err_tok == NEWLINE)
		ft_printf("minishell: No ALNUM value after redirect\n");
	if (err_tok == NO_FILE && str != NULL)
		ft_printf("minishell: %s: No such file or directory", str);
	if (err_tok == AMBIGOUS_REDIRECT)
		ft_printf("minishell: ambiguous redirect\n");
	if (err_tok == DENIED || str != NULL)
		ft_printf("minishell: %s permission denied\n", str);
	return (false);
}
