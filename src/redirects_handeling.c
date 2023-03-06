/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handeling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:07:08 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/06 19:22:25 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

// Assuming if both sides of the redirect are found like <     >
// then we error

int	scan_string(char *str, int found)
{
	int found2;
	if (!str)
		return (-1);
	found = ft_search_c(str, '>', '\'');
	found2 = ft_search_c(str, '<', '\'');
	if (found != -1 && found2 != -1)
		return (-1);
	if (found != -1)
		return (found);
	if (found2 != -1)
		return (found2);
	return (-1);
}
/**
 * @brief This is getting messy I need to refactor this code
 * 
 * @note edge case: ls >       >output.txt = error
 * 
 * @note Refactoring complete. BUT I have to implement the logic
 * that multiple redirects have to be accounted for
 * so for example if we have ls >>   a> I'm only getting >>   a 
 * and the 2nd > is missing so far
*/
char *cut_out(char *str, int start, t_data *data)
{
	char *res;
	int	len;

	len = start;
	if (!str)
		return (NULL);
	while (str[len] && incl_char(str[len], " ><"))
		len++;
	while (str[len] && !incl_char(str[len], " ><"))
		len++;
	len -= start;
	res = ft_substr(str, start, len);
	if (!res)
		return (NULL);
	while (res[data->redir_cnt] && res[data->redir_cnt] == res[0])
		data->redir_cnt++;
	return (res);
// printf("|%d| |%d|", str[len + start], len);
}

/**
 * @note 2. while loop checks if there is sth like >      >
 * @note 3. while loop checks if there is an alnum value
 * @note Missing functionality: correct error msg. Example: > or >> when
 * cnt = 3 or cnt = 4 respectively
 * @note I need to find a different way to send the error messages
 * I was thinking that I could build a wrapper around ft_printf and send the 
 * correct msg then 
*/
bool	check_syntax(char *str, char c, int cnt)
{
	int	i;

	i = cnt - 1;
	if (cnt > 2) // minishell: syntax error near unexpected token `%c'\n
		return (err_msg("unexpexted token\n"), false);
	while (str[i])
	{
		i++;
		if (str[i] && ft_isalnum(str[i]))
			break;
		if (incl_char(str[i], "><"))
			return (err_msg("unexpexted token 2\n"), false);
	}
	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			break ;
		i++;
		if (str[i] == '\0')
			return (err_msg("newline\n"), false); // minishell: syntax error near unexpected token `newline'
	}
	return (true);
}

/**
 * @brief Semantic meaning of check_sematics
 * 
 * @param symbol is the redirection character itself
 * @note the case I'm considering in this version of the code is that
 * I'm only checking one redirect pair (red and red_arg) so at this
 * point it is still not 100% sure if all erros are considered. That
 * being said creating a file before I know if the code error's
 * is the mistake I want to forgo
*/
bool	check_sematics(char *str, char symbol, int cnt, t_data *data)
{
	char	*arg;
	int		spc_len;
	
	spc_len = 0;
	// Earsing Spaces between redirect and red_arg
	while (str[spc_len + cnt] && incl_char(str[spc_len + cnt], " "))
		spc_len++;
	// Change if I refactor del_substr to a bool func
	str = del_substr(str, cnt, spc_len);
	// printf("|%s|\n", str);
	if (!str)
		return (false);
	arg = del_substr(ft_strdup(str), 0, cnt);
	// Guard Clauses Technique
	if (symbol == '>' && cnt == 1)
		return (data->fd = open(arg, O_CREAT | O_WRONLY | O_TRUNC, 0644) , true);
	if (symbol == '>' && cnt == 2)
		return (data->fd = open(arg, O_CREAT | O_WRONLY | O_APPEND, 0644), true);
	// Symbol either '<'
	if (symbol == '<' && cnt == 1 && access(arg, F_OK) == -1)
	{
		err_msg("No such file or directory");
		return (false); // bash: test: No such file or directory
	}
	// Idk if there is anything I need to do for '<<' yet
	return (true);
}

/**
 * @brief redirect main wrapper
 * 
 * @note I have too do 2 more things here
 * 1. Make it work for multiple redirects
 * 2. What happens after I'm done with all of this
*/
bool	redirect_pars(char **str, t_data *data)
{
	char *cutout;
	int	found;

	// Checks also if str exsits
	found = scan_string(*str, found);
	if (*str[0] == '\0' || found == -1)
		return (err_msg("empty str or no redirect or unexpexted token 3\n") , false); // change this err
	cutout = cut_out(*str, found, data);
	if (!cutout || !check_syntax(cutout, cutout[0], data->redir_cnt))
		return (false);
	if (!check_sematics(cutout, cutout[0], data->redir_cnt, data))
		return (false);
	return (true);
	
}