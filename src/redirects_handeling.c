/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handeling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:07:08 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/06 13:09:30 by mwilsch          ###   ########.fr       */
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

	// printf("|%s|\n", str);

bool	redirect_rules(char *str, char symbol, int cnt)
{
	int spc_len;
	
	spc_len = 0;
	// Earsing Spaces between redirect and red_arg
	while (str[spc_len + cnt] && incl_char(str[spc_len + cnt], " "))
		spc_len++;
	// Change if I refactor del_substr to a bool func
	printf("|%s|%d\n", str, spc_len);
	str = del_substr(str, cnt, spc_len);
	printf("|%s|\n", str);
	if (!str)
		return (false);
	
	return (true);
}


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
	redirect_rules(cutout, cutout[0], data->redir_cnt);
	return (true);
}