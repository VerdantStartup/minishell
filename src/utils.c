/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:02:25 by verdant           #+#    #+#             */
/*   Updated: 2023/03/03 21:25:34 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

// void	err_msg(char *msg)
// {
// 	printf("%s", msg);
// }

bool	is_quotes_closed(char *input)
{
	int	i;
	int	cnt;
	int	cnt2;

	i = 0;
	cnt = 0;
	cnt2 = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			cnt++;
		if (input[i] == '\"')
			cnt2++;
		i++;
	}
	if ((cnt % 2) == 0 && (cnt2 % 2) == 0)
		return (true);
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

int	ft_search_c(char *str, char c, char skip)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == skip) // Could be it's own int function i += skip()
		{
			i++;
			while (str[i] != skip && str[i + 1] != '\0')
				i++;
		}
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	count_occurences_skip(char *str, char c, char *skip) // what if skip is nothing?
{
	int	i;
	int	cnt;
	
	i = 0;
	cnt = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (incl_char(str[i], skip)) // Could be it's own int function i += skip()
		{
			i++;
			while (!incl_char(str[i], skip) && str[i + 1] != '\0')
				i++;
		}
		if (str[i] == c)
			cnt++;
		i++;
	}
	return (cnt);
}
