/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handeling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:07:08 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/05 15:39:57 by mwilsch          ###   ########.fr       */
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
 * @note I will refactor the function that I achieve the following goals
 * 1. Count len until end of redirect argument
 * 2. Substr everything out
 * 3. Perform Syntax Checks on unedited string
 * 4. Only then earse the spaces between > & >arg
 * 
 * The trade off of this is that I possibly have to substr more data
 * but the gain is that I have more readable code
*/
char *cut_out(char *str, int start, t_data *data)
{
	int	len;

	len = start;
	if (!str)
		return (NULL);
	while (str[len] && incl_char(str[len], " ><"))
		len++;
	while (str[len] && !incl_char(str[len], " ><"))
		len++;
	len -= start;
	return (ft_substr(str, start, len));
// printf("|%d| |%d|", str[len + start], len);
}

bool	check_syntax(char *str, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	printf("|%s|\n", str);


	// Checking for quantity of redirects
	while (str[cnt] == c)
		cnt++;
	// I could use variadic arugments to make this into a one-liner by 
	// using err_msg as a wrapper for printf and put it into return
	printf("|%d|\n", cnt);
	if (cnt > 2) // minishell: syntax error near unexpected token `%c'\n
		return (err_msg("unexpexted token\n"), false);

	// Checking if there is no redirect argument
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
	// Checking if for example: >        > or <       >
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
	cutout = cut_out(*str, found, data);// Refactor
	if (!cutout || !check_syntax(cutout, cutout[0]))
		return (false);
	return (true);
}