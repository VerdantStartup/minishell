/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:52:23 by verdant           #+#    #+#             */
/*   Updated: 2023/03/01 17:23:38 by mwilsch          ###   ########.fr       */
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
	char *env_var;
	char *var_res;
	int start;
	int	len;
	int	i;


	start = 0;
	len = 0;
	if (str[0] == '\0' || count_occurences(str, '$') == 0)
		return (err_msg("Str empty or no $"), true);
	start = ft_strclen(str, '$') + 1;
	i = start;
	while (str[i] && !is_delim(str[i], data->delimiter))
	{
		len++;
		i++;
	}
	env_var = ft_substr(str, start, len);
	if (!env_var)
		return (err_msg("HERE") ,free(env_var), false);
	var_res = getenv(env_var);
	if (!var_res)
		return (err_msg("HERE1"), free(env_var), false);
	printf("%s", var_res);
	return (true);
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
	free_split(path_mod);
	if (path_mod[i] == NULL)
		return (err_msg("Command not found"),false);
	ft_memmove(str, str + data->spc_cmd_len, ft_strlen(str));
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
		if (!cmd_res(arr[i], &cmds[i], &data) || !env_res(arr[i], &data))
			return (1);
		// printf("%d\n", arr[i][0]);
		i++;
	}
	// ft_split_ultimate(input, " ", "><", "\'\"");
}


// With the remaining string I need to take care of two things
// 1. Quotation
	// 1.1 Everything between a quote will not be splitted even if a other delimiter is encounted
	// 1.2 The quote itself is not a reason to split either
	// 1.3 The quotes need to be preserved for further evulation later one
// 2. Redirects 
	// 1. If a redirect is encountered the string will be splitted
	// 2. The redirect needs to be preserved
	

