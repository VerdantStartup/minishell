 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:57:38 by verdant           #+#    #+#             */
/*   Updated: 2023/03/03 21:21:59 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"


// Helper for cmd_resolution

bool	prep_cmd(char *str, t_cmd *cmd, t_data *data)
{
	int	len;
	int i;
	int k;

	len = 0;
	i = 1; // because name[0] = /
	k = 0;
	while (str[k] && str[k] == ' ') // Skipping over spaces
		k++;
	while (str[len + k] && !incl_char(str[len + k], data->delim))
		len++;
	data->spc_cmd_len = len + k;
	cmd->name = malloc(sizeof(char) * (len + 2));
	if (!cmd->name)
		return (false);
	cmd->name[len + 1] = '\0';
	cmd->name[0] = '/';
	while (i < len + 1)
		cmd->name[i++] = str[k++];
	return (true);
}

char	*add_to_arr(char *string,char *string_to_add, int size)
{
	int	i;
	char	*temp;

	i = 0;
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp[size] = '\0';
	while (i < size)
	{
		temp[i] = string_to_add[i];
		i++;
	}
	free(string);
	return (temp);
}

// Helper for main function

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

// Helper for env_resolution





