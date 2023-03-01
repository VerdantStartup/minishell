/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:57:38 by verdant           #+#    #+#             */
/*   Updated: 2023/03/01 18:54:41 by mwilsch          ###   ########.fr       */
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
	while (str[len + k] && !is_delim(str[len + k], data->delimiter))
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

// Helper for cmd_resolution

bool	substitute_var(char *str, char *env_var)
{
	const int		size = ft_strlen(str) + ft_strlen(var_res);
	char				*temp;
	int					i;

	i = 0;	
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (false);
	temp[size] = '\0';
	while (str[i] && i < size)
	{
		temp[i] = str[i];
		i++;
		if (str[i] == '$')
		{
			while ()
		}
	}
}

// Helper for cmd_resolution

char	*add_to_arr(char *string,char *string_to_add, int size)
{
	int	i;
	char	*temp;

	i = 0;
	// printf("%d %s\n",size,  string_to_add);
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
	data->delimiter = " <>";
	data->cmd_cnt = 1;
	data->cmd_cnt += count_occurences(input, '|');
	cmds = malloc(sizeof(t_cmd) * (data->cmd_cnt));
	if (!cmds)
		return (NULL);
	return (cmds);
}

