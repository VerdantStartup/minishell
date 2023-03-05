/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:52:23 by verdant           #+#    #+#             */
/*   Updated: 2023/03/05 15:38:39 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

// Add this one to libft
void	free_split(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

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
	// char				*input = "ls <     >"; // Use when DEBUG=1
	char				**arr;
	t_cmd				*cmds;
	t_data			data;
	int					i;
	
	
	i = 0;
	cmds = structs_init(input, cmds, &data);
	// Fix for multiple quotes
	if (!cmds || !are_quotes_even(input)) 
	{
		puts("TEST");
		return (1);
	}
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
}
