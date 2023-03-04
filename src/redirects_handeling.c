/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_handeling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 12:07:08 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/04 17:50:10 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

int	scan_string(char *str, int found)
{	
	if (!str)
		return (-1);
	found = ft_search_c(str, '>', '\'');
	if (found != -1)
		return (found);
	found = ft_search_c(str, '<', '\'');
	if (found != -1)
		return (found);
	return (-1);
}


/**
 * @brief This is getting messy I need to refactor this code
 * 
 * @note edge case: ls >       >output.txt = error
*/
char	*cut_out(char *str, int start, t_data *data)
{
	int		len;
	int		i;
	int		earser;
	
	i = start + 1;
	len = 1;
	earser = 0;
	// checking if it's one or a a two redirect pair
	if (str[i] != ' ') // what about other white space?
	{
		len++;
		i++;
	} 
	// Skipping over whitespace between redirect and red argument
	while (incl_char(str[i], " \t"))
	{
		i++;
		earser++;
		if (incl_char(str[i], "<>")) // This has to depend on the right redirect tho
			return (err_msg("syntax error near unexpected token `>'\n"), NULL);
	}
	i -= earser;
		str = delete_substr(str, start + len, earser);
	while (str[i] && !incl_char(str[i], ">< "))
	{
		len++;
		i++;
	}
	return (ft_substr(str, start, len));
}


// bool	check_syntax(char *str, char c)
// {
// 	int	cnt;

// 	cnt = 0;
// 	if (!str)
// 		return (false);
// 	printf("%s\n", str);
// 	while (str[cnt] && str[cnt] == c)
// 		cnt++;
// 	printf("CNT: %d\n", cnt);
// 	return (true);
// }

bool	redirect_pars(char **str, t_data *data)
{
	char *cutout;
	int	found;

	// Checks also if str exsits
	found = scan_string(*str, found);
	if (*str[0] == '\0' || found == -1)
		printf("empty str or no redirect\n");
	cutout = cut_out(*str, found, data); // Refactor
	// if (!cutout || !check_syntax(cutout, cutout[0]))
	// 	return (false);
	return (true);
}