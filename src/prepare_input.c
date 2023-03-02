/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Verdant <Verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:52:23 by verdant           #+#    #+#             */
/*   Updated: 2023/03/02 19:20:25 by Verdant          ###   ########.fr       */
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

bool	env_res(char *str, t_data *data)
{
	const int	cnt = count_occurences(str, '$');
	int	i;

	i = 0;
	// Checking if Env Var exits
	if (str[0] == '\0' || cnt <= 0 || str_literal(str));
		return (err_msg("Str empty or no $"), true);

	// I need to build a check where a $ inside a string does not get subsituted
	// But if there is a $ outside of that I need to somehow still subsitute that - fuck yah

	while (i < cnt)
	{
		str = substitute_var(str, get_env(str, data), data->env_len + 1, data);
		data->env_len = 0;
		i++;
	}
	printf("%s\n", str);
	return (true);
}

// echo -n "$HOME and some text"

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
	if (path_mod[i] == NULL)
		return (free_split(path_mod), err_msg("Command not found"),false);
	free_split(path_mod);
	ft_memmove(str, str + data->spc_cmd_len, ft_strlen(str));
	return (true);
}

int main(int argc, char *argv[])
{
	char				*input = readline(""); // Reading the cmd line input
	// char				*input = "echo -n \"$HOME and some text\"";
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
		if (!cmd_res(arr[i], &cmds[i], &data) || !env_res(arr[i], &data))
			return (1);
		// printf("%d\n", arr[i][0]);
		i++;
	}
}


// With the remaining string I need to take care of two things
// 1. Quotation
	// 1.1 Everything between a quote will not be splitted even if a other delimiter is encounted
	// 1.2 The quote itself is not a reason to split either
	// 1.3 The quotes need to be preserved for further evulation later one
// 2. Redirects 
	// 1. If a redirect is encountered the string will be splitted
	// 2. The redirect needs to be preserved
	

