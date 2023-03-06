/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:45:51 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/06 13:09:07 by mwilsch          ###   ########.fr       */
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