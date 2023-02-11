/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:52:31 by mwilsch           #+#    #+#             */
/*   Updated: 2023/02/11 16:13:03 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
Test





#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	// char *cmd_line_input = readline(""); // Reading the cmd line input
	char **splitted = ft_split(cmd_line_input, '>');
	char **splitted2 = ft_split(splitted[1], '|');
	int i = 0;
	while (splitted[i])
	{
		printf("%s\n", splitted[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (splitted2[i])
	{
		printf("%s\n", splitted2[i]);
		i++;
	}
}


