/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:21:11 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/07 19:41:13 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"


char	*add_to_arr(char *string,char *str_to_add, int size)
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
		temp[i] = str_to_add[i];
		i++;
	}
	free(string);
	return (temp);
}

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


/**
 * 
 * @note del_substr at the end is to delete the cmd from the string
*/
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
			// I could refactor add_to_arr to be a bool and then not return it into cmd name
			cmd->name = add_to_arr(cmd->name, path_mod[i], ft_strlen(path_mod[i])); 
			break;
		}
		i++;
	}
	if (path_mod[i] == NULL)
		return (free_split(path_mod), error_syntax(cmd->name + 1, NO_CMD));
	free_split(path_mod);
	del_substr(str, 0, data->spc_cmd_len);
	return (true);
}