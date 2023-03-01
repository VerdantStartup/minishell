/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:52:23 by verdant           #+#    #+#             */
/*   Updated: 2023/02/28 16:33:19 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



	// char *delimt_set = " <>";
	// char *skip = "\'\"";
	
	// for (int i = 0; arr[i]; i++)
	// 	printf("%s", arr[i]);

#include "testing.h"


// void leaks(void) // Delete when finished
// {
// 	system("leaks -q ./testing");
// }

bool	cmd_res(char *str, t_cmd *cmd, t_data *data)
{
	char *path_var = getenv("PATH");
	char **path_mod = ft_split(path_var, ':');
	int i;

	i = 0;
	if (!prep_cmd(str, cmd, data))
		return (false);
	while(path_mod[i] != NULL)
	{
		path_mod[i] = ft_strjoin(path_mod[i], cmd->name);
		if (access(path_mod[i], X_OK) == 0)
		{
			cmd->name = add_to_arr(cmd->name, path_mod[i], ft_strlen(path_mod[i]));
			break;
		}
		i++;
	}
	free_split(path_mod);
	return (true);
}

int main(int argc, char *argv[])
{
	char				*input = readline(""); // Reading the cmd line input
	char				**arr;
	t_cmd				*cmds;
	t_data			data;
	int					i;
	
	i = 0;
	cmds = structs_init(input, cmds, &data);
	if (!cmds || !is_quotes_closed(input)) // Is this okay?
		return (1);
	arr = ft_split(input, '|');
	// Check if splitting was succesfull // Do this later
	while (i < data.cmd_cnt)
	{
		if (!cmd_res(arr[i], &cmds[i], &data))
			return (1);
		printf("%s\n", arr[i]);
		i++;
	}
	ft_split_ultimate(arr[0], data.delimiter, "\'\"");
}

// With the remaining string I need to take care of two things
// 1. Quotation
	// 1.1 Everything between a quote will not be splitted even if a other delimiter is encounted
	// 1.2 The quote itself is not a reason to split either
	// 1.3 The quotes need to be preserved for further evulation later one
// 2. Redirects 
	// 1. If a redirect is encountered the string will be splitted
	// 2. The redirect needs to be preserved
	

