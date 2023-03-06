/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:52:23 by verdant           #+#    #+#             */
/*   Updated: 2023/03/06 19:26:54 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

t_cmd *structs_init(char *input, t_cmd *cmds, t_data *data)
{	
	if (input[0] == '\0') // I have to change this to reprompt
		return (NULL);
	// data = calloc(sizeof(t_data), 1);
	data->delim = " <>";
	data->skip = "\'\"";
	data->env_len = 0;
	data->env_size = 0;
	data->cmd_cnt = 1;
	data->cmd_cnt += count_occurences_skip(input, '|', NULL);
	data->redir_cnt = 0;
	cmds = malloc(sizeof(t_cmd) * (data->cmd_cnt));
	if (!cmds)
		return (NULL);
	return (cmds);
}

/**
 * @brief  Main
 * 
 * @note I think the things which are left do are
 * 0 Decide to implement or not implement my refactor ideas
 * 1. Executing the redirection
 * 2. Adding a rule for the built-in functions
 * 3. Display a prompt when waiting for a new command.
 * 4. Have a working history.
 * 5. Execution of pipes
 * 6. Signals
 * 
 * @note ambiougs redirect e.g: ls > $HO $HO: ambiguous redirect
 * 
 * @note for err msg I can build a wrapper func in helper2 and use my 
 * declared enums
*/
int main(int argc, char *argv[])
{
	char				*input = readline(""); // Reading the cmd line input
	// char				*input = "ls <     >"; // Use when DEBUG=1
	char				**arr;
	t_cmd				*cmds;
	t_data			data;
	int					i;
	
	i = 0;
	cmds = structs_init(input, cmds, &data);
	if (!cmds || !are_quotes_even(input)) 
		return (1);
	arr = ft_split(input, '|');
	// Check if splitting was succesfull // Do this later
	while (i < data.cmd_cnt)
	{
		if (!cmd_res(arr[i], &cmds[i], &data) || !env_res(&arr[i], &data))
			return (1);
		redirect_pars(&arr[i], &data); // make a if out of this
		// printf("|%s|\n", arr[i]);
		// printf("%s\n", cmds[i].name);
		i++;
	}
	printf("%s", arr[0]);
}
