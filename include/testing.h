/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:22:26 by mwilsch           #+#    #+#             */
/*   Updated: 2023/02/11 15:35:11 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_H
#define TESTING_H

# include <readline/readline.h>
# include <stdbool.h>
# include "../libft/include/libft.h"
# include "stdio.h"

enum tokens {
	COMMANDS,
	CMD_ARGS,
	ENV_VAR,
	
};

typedef struct s_command {
	char	*name;           // The name of the command
	int		num_args;         // The number of arguments for the command
	char	**args;          // The names of the arguments for the command
	char	**oper;					// Operaters & their files
	void (*func)();       // The function pointer to the implementation code
} t_cmd;


#endif