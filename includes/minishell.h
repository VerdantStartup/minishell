/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:10:49 by tklouwer          #+#    #+#             */
/*   Updated: 2023/02/07 14:46:33 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <string.h>

typedef struct      s_comm_table t_comm_table;;
typedef struct      s_data t_data;

typedef struct s_data
{
    t_comm_table    *comm_table;
}              t_data;

typedef struct      s_comm_table
{
    char            **command;
}                   t_comm_table;

void rl_replace_line(const char *text, int clear_undo);

#endif