/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:45:51 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/04 17:26:04 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

char	*delete_substr(char *str, int start, int len)
{
	int	copy_from;

	copy_from = start + len;
	while (str[copy_from])
		str[start++] = str[copy_from++];
	str[start] = '\0';
	return (str);
}