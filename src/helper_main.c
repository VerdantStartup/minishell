/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:57:38 by verdant           #+#    #+#             */
/*   Updated: 2023/03/03 13:21:32 by mwilsch          ###   ########.fr       */
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

// Helper for env_resolution

char	*get_env(char *str, t_data *data)
{
	const int	start = ft_strclen(str, '$') + 1;
	char			*env_var;
	int				i;

	// printf("%s\t%d\n", str, start);
	i = start;
	
	while (str[i] && !is_delim(str[i], data->delimiter) && !is_skip(str[i], data->skip))
	{
		data->env_len++;
		i++;
	}
	env_var = getenv(ft_substr(str, start, data->env_len));
	if (!env_var)
		return (free(env_var), NULL);
	// printf("%s\n", env_var);
	return (env_var);
}

// Helper for env_resolution

// "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin and $HOME"

char *erase_wrg_var(char *str, t_data *data)
{
	int	start;
	int	end;
	int	i;

	start = ft_strclen(str, '$');
	end = data->env_len + 1 + start;

	// printf("%d", end);

	ft_memmove(str + start, str + end + 1, ft_strlen(str) - end); // Tf is this working - ChatGPT is a crazy
	// printf("%s", str);


	return (str);
}

// "/Users/Verdant and $HOE"

char	*substitute_var(char *str, char *env_var, int env_len, t_data *data)
{
	const int		size = ft_strlen(str) + ft_strlen(env_var) - env_len;
	char				*temp;
	int					i;
	int					k;
	int					temp_i;

	i = 0;
	k = 0;

	if (!env_var)
		return (erase_wrg_var(str, data));
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp[size] = '\0';
	
	// Copy everything before $
	while (str[i] && str[i] != '$')
	{
		temp[i] = str[i];
		i++;
	}
	temp_i = env_len + i;
	// Copy everything from env_var
	while (env_var[k])
		temp[i++] = env_var[k++];
	// Copy the remaining chars to temp;
	while (str[temp_i])
		temp[i++] = str[temp_i++];
	free(str);
	return (temp);
}

// Helper for cmd_resolution

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
	data->delimiter = " <>";
	data->skip = "\'\"";
	data->env_len = 0;
	data->cmd_cnt = 1;
	data->cmd_cnt += count_occurences(input, '|');
	cmds = malloc(sizeof(t_cmd) * (data->cmd_cnt));
	if (!cmds)
		return (NULL);
	return (cmds);
}

