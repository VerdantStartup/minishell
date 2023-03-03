/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:22:26 by mwilsch           #+#    #+#             */
/*   Updated: 2023/03/03 16:59:53 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_H
#define TESTING_H

# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/include/libft.h"

enum tokens {
	COMMANDS,
	CMD_ARGS,
	ENV_VAR,
};

// typedef struct s_cmd_resolution {
// 	int	pipe_index[];
// 	int	cmd_cnt;
// } t_cmd_res;


typedef struct s_command {
	char	*name;           // The name of the command
	int		num_args;         // The number of arguments for the command
	char	**args;          // The names of the arguments for the command
	char	**oper;					// Operaters & their files
	void (*func)();       // The function pointer to the implementation code
} t_cmd;

typedef struct s_data {
	int		cmd_cnt;
	int		spc_cmd_len;
	int		env_len;
	int		env_start;
	char	*delimiter;
	char	*skip;
} t_data;


/**
 * @brief Utility files which are used wherever
 * 
 */
bool	is_quotes_closed(char *input);
bool	is_delim(char c, char *delimiters);
bool	is_skip(char c, char *skip);
int		count_occurences(char *input, char c);
void	free_split(char **arr);
void	err_msg(char *msg);

/**
 * @brief Utily functions which are used in my main file
 * 
 */
t_cmd *structs_init(char *input, t_cmd *cmds, t_data *data);
char	*add_to_arr(char *string, char *string_to_add, int size);
bool	prep_cmd(char *str, t_cmd *cmd, t_data *data);
char	*substitute_var(char *str, char *env_var, int env_len, t_data *data);
char	*get_env(char *str, t_data *data);

int	ft_search_c(char *str, char c, char skip);
int	count_occurences_skip(char *str, char c, char skip);


// char **ft_split_ultimate(char *line, char *delim_skip, char *delim_keep, char *keep);





#endif